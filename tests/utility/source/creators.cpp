#include "creators.hpp"
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

std::shared_ptr<Effect> create_poisoning(std::shared_ptr<Effected> target){
    unsigned strength = 3;
    unsigned ticks = 15;
    return std::make_shared<Poisoning>(target, strength, ticks);
}

std::shared_ptr<Effect> create_weakening(std::shared_ptr<Effected> target){
    unsigned strength = 3;
    unsigned ticks = 15;
    return std::make_shared<Weakening>(target, strength, ticks);
}

std::shared_ptr<Effect> create_slowdown(std::shared_ptr<Effected> target){
    unsigned strength = 3;
    unsigned ticks = 15;
    return std::make_shared<Slowdown>(target, strength, ticks);
}

std::shared_ptr<Entity> create_bob(ISystemManager& manager, IFactoryManager& f_manager){
    hp_t bob_hp = 100;
    double bob_speed = 50;
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

std::shared_ptr<Entity> create_tank(ISystemManager& manager, IFactoryManager& f_manager){
    hp_t tank_hp = 300;
    double tank_speed = 15;
    hp_t tank_damage = 30;
    unsigned tank_gold = 300;
    Coordinates tank_position = {1, 1};
    std::shared_ptr<Enemy> tank = std::make_shared<Enemy>(manager,
                                                         tank_hp,
                                                         tank_speed,
                                                         tank_damage,
                                                         tank_gold,
                                                         tank_position);
    return std::static_pointer_cast<Entity>(tank);
}


std::shared_ptr<Entity> create_simple_tower(ISystemManager& manager, IFactoryManager& f_manager, TowerNode& node){
    hp_t t_hp = 100;
    hp_t t_damage = 50;
    Coordinates t_position = {1, 1};
    unsigned t_cost = node.cost;
    double t_vision = 4;
    double t_rapidity = 25;
    std::vector<std::unordered_map<std::string, std::string>> levelup_table;
    return std::make_shared<Tower>(
        manager,
        t_hp,
        Coordinates{1, 1},
        t_cost, 
        t_vision,
        t_damage,
        t_rapidity,
        levelup_table
    );
}

std::shared_ptr<Entity> create_magic_tower(ISystemManager& manager, IFactoryManager& f_manager, TowerNode& node){
    hp_t t_hp = 100;
    hp_t t_damage = 5;
    Coordinates t_position = {1, 1};
    unsigned t_cost = node.cost;
    double t_vision = 5;
    double t_rapidity = 10;
    std::vector<std::unordered_map<std::string, std::string>> levelup_table;
    std::unordered_map<std::string, MagicNode> effects;
    effects["poison"] = {7, 220};
    effects["slow"] = {5, 300};
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

std::shared_ptr<Entity> create_simple_trap(ISystemManager& manager, IFactoryManager& f_manager, TrapNode& node){
    Coordinates pos = {1, 2};
    unsigned cost = node.cost;
    double vision = 1;
    double effect_radius = 7;
    hp_t damage = 100;
    if (node.trap_level >= 2){
        damage += 5;
        vision += 1;
        cost += 50;
    }
    return std::make_shared<Trap>(
        manager,
        pos,
        cost,
        vision,
        effect_radius,
        damage
    );
}
std::shared_ptr<Entity> create_magic_trap(ISystemManager& manager, IFactoryManager& f_manager, TrapNode& node){
    Coordinates pos = {1, 2};
    unsigned cost = node.cost;
    double vision = 2.28;
    double effect_radius = 3;
    hp_t damage = 10;
    std::unordered_map<std::string, MagicNode> magic_effects;
    magic_effects["poison"] = {1, 1};
    if (node.trap_level >= 2){
        damage += 5;
        vision += 1;
        cost += 50;
        magic_effects["weak"] = {2, 2};
    }
    return std::make_shared<MagicTrap>(
        manager,
        f_manager.get_effect_factory(),
        pos,
        cost,
        vision,
        effect_radius,
        damage,
        magic_effects
    );
}
