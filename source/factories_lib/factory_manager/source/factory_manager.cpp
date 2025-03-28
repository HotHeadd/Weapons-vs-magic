#include "factory_manager.hpp"

namespace WVM
{   

FactoryManager::FactoryManager(ISystemManager& manager)
: enemy_factory_(EnemyFactory(manager, *this)), tower_factory_(TowerFactory(manager, *this)), trap_factory_(TrapFactory(manager, *this)), effect_factory_() {}

EnemyFactory& FactoryManager::get_enemy_factory(){
    return enemy_factory_;
}

TowerFactory& FactoryManager::get_tower_factory(){
    return tower_factory_;
}

TrapFactory& FactoryManager::get_trap_factory(){
    return trap_factory_;
}

EffectFactory& FactoryManager::get_effect_factory(){
    return effect_factory_;
}

} // namespace WVM