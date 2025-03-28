#include "magic_trap.hpp"

namespace WVM
{

MagicTrap::MagicTrap(
    ISystemManager& manager,
    IEffectFactory& factory,
    Coordinates position,
    unsigned cost,
    double vision_radius,
    double effect_radius,
    hp_t damage,
    std::unordered_map<std::string, MagicNode>& magic_effects) : 
        Magic(factory),
        Trap(manager, position, cost, vision_radius, effect_radius, damage) {
    magic_effects_ = magic_effects;
}

void MagicTrap::affect_target(std::shared_ptr<Entity> target){
    std::shared_ptr<IEnemy> e_target = std::static_pointer_cast<IEnemy>(target);
    std::lock_guard<std::mutex> lock_enemy(e_target->mutex());
    cast_spell(e_target);
    e_target->take_damage(damage_);
}

} // namespace WVM
