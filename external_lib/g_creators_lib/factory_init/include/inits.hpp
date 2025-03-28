#include "i_enemy_factory.hpp"
#include "i_tower_factory.hpp"
#include "i_trap_factory.hpp"
#include "i_effect_factory.hpp"

using namespace WVM;

extern "C" void register_enemies(IEnemyFactory& factory);
extern "C" void register_towers(ITowerFactory& factory);
extern "C" void register_traps(ITrapFactory& factory);
extern "C" void register_effects(IEffectFactory& factory);