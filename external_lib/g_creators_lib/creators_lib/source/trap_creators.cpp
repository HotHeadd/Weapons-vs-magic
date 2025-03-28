#include "trap_creators.hpp"
#include "g_trap.hpp"
#include "g_magic_trap.hpp"
#include "g_nodes.hpp"


std::shared_ptr<Entity> create_simple_trap(ISystemManager& manager, IFactoryManager& f_manager, TrapNode& node){
    GTrapNode& gnode = static_cast<GTrapNode&>(node);
    Coordinates pos = {1, 2};
    unsigned cost = node.cost;
    double vision = 1;
    double effect_radius = 7;
    hp_t damage = 300;
    if (node.trap_level >= 2){
        damage += 5;
        vision += 1;
        cost += 50;
    }
    return std::make_shared<GTrap>(
        manager,
        pos,
        cost,
        vision,
        effect_radius,
        damage,
        gnode.texture_path
    );
}
std::shared_ptr<Entity> create_magic_trap(ISystemManager& manager, IFactoryManager& f_manager, TrapNode& node){
    GTrapNode& gnode = static_cast<GTrapNode&>(node);
    Coordinates pos = {1, 2};
    unsigned cost = node.cost;
    double vision = 2.28;
    double effect_radius = 3;
    hp_t damage = 10;
    std::unordered_map<std::string, MagicNode> magic_effects;
    magic_effects["poison"] = {10, 300};
    magic_effects["slow"] = {4, 210};
    if (node.trap_level >= 2){
        damage += 5;
        vision += 1;
        cost += 50;
        magic_effects["weak"] = {2, 2};
    }
    return std::make_shared<GMagicTrap>(
        manager,
        f_manager.get_effect_factory(),
        pos,
        cost,
        vision,
        effect_radius,
        damage,
        magic_effects,
        gnode.texture_path
    );
}
