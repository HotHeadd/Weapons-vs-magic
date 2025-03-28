#include "tower_creators.hpp"

#include "magic_tower.hpp"
#include "i_sys_manager.hpp"
#include "i_factory_manager.hpp"

#include "g_nodes.hpp"
#include "g_tower.hpp"
#include "g_magic_tower.hpp"

std::shared_ptr<Entity> create_simple_tower(ISystemManager& manager, IFactoryManager& f_manager, TowerNode& node){
    GTowerNode& gnode = static_cast<GTowerNode&>(node);
    hp_t t_hp = 100;
    hp_t t_damage = 100;
    Coordinates t_position = {1, 1};
    unsigned t_cost = node.cost;
    double t_vision = 4;
    double t_rapidity = 100;
    std::vector<std::unordered_map<std::string, std::string>> levelup_table;
    return std::make_shared<GTower>(
        manager,
        t_hp,
        Coordinates{1, 1},
        t_cost, 
        t_vision,
        t_damage,
        t_rapidity,
        levelup_table,
        gnode.texture_path
    );
}

std::shared_ptr<Entity> create_magic_tower(ISystemManager& manager, IFactoryManager& f_manager, TowerNode& node){
    GTowerNode& gnode = static_cast<GTowerNode&>(node);
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
    return std::make_shared<GMagicTower>(
        manager,
        f_manager.get_effect_factory(),
        t_hp,
        Coordinates{1, 1},
        t_cost, 
        t_vision,
        t_damage,
        t_rapidity,
        levelup_table,
        effects,
        gnode.texture_path
    );
}