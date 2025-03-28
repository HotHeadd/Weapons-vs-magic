#pragma once

#include "i_effect_factory.hpp"
#include "i_enemy_factory.hpp"
#include "i_tower_factory.hpp"
#include "i_trap_factory.hpp"

namespace WVM
{

class IFactoryManager {
public:
    virtual IEnemyFactory& get_enemy_factory() = 0;
    virtual ITowerFactory& get_tower_factory() = 0;
    virtual ITrapFactory& get_trap_factory() = 0;
    virtual IEffectFactory& get_effect_factory() = 0;
};

} // namespace WVM
