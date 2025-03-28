#include "game.hpp"
#include "enemy_system.hpp"
#include "lair_system.hpp"
#include "lair.hpp"

#include <dlfcn.h>

namespace WVM
{

Game::Game(std::shared_ptr<Layout> layout, std::shared_ptr<Castle> castle, std::string_view init_level_name)
: system_manager_(SystemManager(layout, castle)), fact_manager_(FactoryManager(system_manager_)), level_name(init_level_name) {}

void Game::load_config(const std::string& lib_name){
    using register_enemy_factory = void(*)(IEnemyFactory&);
    using register_tower_factory = void(*)(ITowerFactory&);
    using register_trap_factory = void(*)(ITrapFactory&);
    using register_effect_factory = void(*)(IEffectFactory&);

    std::string path_to_lib = std::string("assets/plugins/") + lib_name;
    void* dynamic = dlopen(path_to_lib.data(), RTLD_NOW);
    if (!dynamic){
        throw std::logic_error("Load config: can't open dynamic library");
    }
    auto register_enemies = reinterpret_cast<register_enemy_factory>(dlsym(dynamic, "register_enemies"));
    auto register_towers = reinterpret_cast<register_tower_factory>(dlsym(dynamic, "register_towers"));
    auto register_traps = reinterpret_cast<register_trap_factory>(dlsym(dynamic, "register_traps"));
    auto register_effects = reinterpret_cast<register_effect_factory>(dlsym(dynamic, "register_effects"));
    if (register_enemies and register_towers and register_traps and register_effects){
        register_enemies(fact_manager_.get_enemy_factory());
        register_towers(fact_manager_.get_tower_factory());
        register_traps(fact_manager_.get_trap_factory());
        register_effects(fact_manager_.get_effect_factory());
    }
    else{
        throw std::logic_error("Load config: error loading. One of register funcitons is missing");
    }
    dlclose(dynamic);
    lib_name_ = lib_name;
}

void Game::update(){
    for (auto& system_pair : system_manager_){
        system_pair.second->update();
    }
}

void Game::refresh(){
    for (auto& system_pair : system_manager_){
        system_pair.second->refresh();
    }
    current_wave_ += 1;
}

bool Game::wave_end(){
    if (!system_manager_.get_system(SystemTag::LAIR).is_empty()){
        return false;
    }
    if (!system_manager_.get_system(SystemTag::ENEMY).is_empty()){
        return false;
    }
    return true;
}

bool Game::game_over(){
    return system_manager_.get_castle().hp() <= 0;
}

std::shared_ptr<ILair> Game::add_lair(Coordinates position, std::vector<std::unordered_map<std::string, LairNode>> instr){
    if (system_manager_.get_layout()(position).type() != TileType::ROAD){
        return nullptr;
    }
    for (auto& lair : system_manager_.get_lairs()){
        if (lair->position().x == position.x  and lair->position().y == position.y){
            return nullptr;
        }
    }
    std::shared_ptr<Lair> new_lair = std::make_shared<Lair>(system_manager_, fact_manager_.get_enemy_factory(), position, instr);
    system_manager_.get_system(SystemTag::LAIR).add(new_lair);
    return new_lair;
}

std::shared_ptr<ILair> Game::add_empty_lair(Coordinates position){
    if (system_manager_.get_layout()(position).type() != TileType::ROAD){
        return nullptr;
    }
    for (auto& lair : system_manager_.get_lairs()){
        if (lair->position().x == position.x  and lair->position().y == position.y){
            return nullptr;
        }
    }
    std::shared_ptr<Lair> new_lair = std::make_shared<Lair>(system_manager_, fact_manager_.get_enemy_factory(), position);
    system_manager_.get_system(SystemTag::LAIR).add(new_lair);
    return new_lair;
}

Layout& Game::layout(){
    return system_manager_.get_layout();
}

Castle& Game::castle(){
    return system_manager_.get_castle();
}

std::unordered_map<std::string, std::unique_ptr<TowerNode>>& Game::list_all_towers(){
    return fact_manager_.get_tower_factory().creators();
}

std::unordered_map<std::string, std::unique_ptr<TrapNode>>& Game::list_all_traps(){
    return fact_manager_.get_trap_factory().creators();
}

std::shared_ptr<ITower> Game::add_tower(std::string tower_name, Coordinates position){
    if (layout()(position).type() != TileType::FIELD){
        return nullptr;
    }
    std::shared_ptr<ITower> new_tower = std::static_pointer_cast<ITower>(fact_manager_.get_tower_factory().create(tower_name));
    new_tower->move(position);
    system_manager_.get_system(SystemTag::DEFENCE).add(new_tower);
    system_manager_.get_system(SystemTag::EFFECT).add(new_tower);
    return new_tower;
}

std::shared_ptr<ITrap> Game::add_trap(std::string trap_name, Coordinates position){
    if (layout()(position).type() != TileType::ROAD){
        return nullptr;
    }
    std::shared_ptr<ITrap> new_trap = std::static_pointer_cast<ITrap>(fact_manager_.get_trap_factory().create(trap_name));
    new_trap->move(position);
    system_manager_.get_system(SystemTag::DEFENCE).add(new_trap);
    system_manager_.get_system(SystemTag::EFFECT).add(new_trap);
    return new_trap;
}

} // namespace WVM
