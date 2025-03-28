#pragma once

#include "i_sys_manager.hpp"
#include "i_factory_manager.hpp"
#include "enemy_factory.hpp"
#include "tower_factory.hpp"
#include "effect_factory.hpp"
#include "trap_factory.hpp"

namespace WVM
{

class FactoryManager : public IFactoryManager{
public:
    FactoryManager(ISystemManager& manager);

    EnemyFactory& get_enemy_factory() override;
    TowerFactory& get_tower_factory() override;
    TrapFactory& get_trap_factory() override;
    EffectFactory& get_effect_factory() override;
private:
    EnemyFactory enemy_factory_;
    EffectFactory effect_factory_;
    TowerFactory tower_factory_;
    TrapFactory trap_factory_;
};

} // namespace WVM
