#include "time_creators.hpp"
#include "poisoning.hpp"
#include "weakening.hpp"
#include "slowdown.hpp"
#include "i_factory_manager.hpp"
#include "enemy.hpp"
#include "tower.hpp"
#include "magic_tower.hpp"
#include "i_sys_manager.hpp"
#include "trap.hpp"
#include "magic_trap.hpp"

std::shared_ptr<Effect> poisoning_timetest(std::shared_ptr<Effected> target){
    unsigned strength = 3;
    unsigned ticks = 15;
    return std::make_shared<Poisoning>(target, strength, ticks);
}

std::shared_ptr<Effect> slowdown_timetest(std::shared_ptr<Effected> target){
    unsigned strength = 3;
    unsigned ticks = 15;
    return std::make_shared<Slowdown>(target, strength, ticks);
}

std::shared_ptr<Entity> bob_timetest(ISystemManager& manager, IFactoryManager& f_manager){
    hp_t bob_hp = 100;
    double bob_speed = 1000;
    hp_t bob_damage = 10;
    unsigned bob_gold = 100;
    Coordinates bob_position = {1, 1};
    std::shared_ptr<Enemy> bob = std::make_shared<Enemy>(manager,
                                                         bob_hp,
                                                         bob_speed,
                                                         bob_damage,
                                                         bob_gold,
                                                         bob_position);
    return std::static_pointer_cast<Entity>(bob);
}
std::shared_ptr<Entity> magic_tower_timetest(ISystemManager& manager, IFactoryManager& f_manager, TowerNode& node){
    hp_t t_hp = 100;
    hp_t t_damage = 3;
    Coordinates t_position = {1, 1};
    unsigned t_cost = node.cost;
    double t_vision = 4;
    double t_rapidity = 500;
    std::vector<std::unordered_map<std::string, std::string>> levelup_table;
    std::unordered_map<std::string, MagicNode> effects;
    effects["poison"] = {5, 220};
    effects["slow"] = {15, 1220};
    return std::make_shared<MagicTower>(
        manager,
        f_manager.get_effect_factory(),
        t_hp,
        Coordinates{1, 1},
        t_cost, 
        t_vision,
        t_damage,
        t_rapidity,
        levelup_table,
        effects
    );
}