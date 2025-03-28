#include "inits.hpp"
#include "enemy_creators.hpp"
#include "tower_creators.hpp"
#include "trap_creators.hpp"
#include "effect_creators.hpp"
#include "g_nodes.hpp"

extern "C" void register_enemies(IEnemyFactory& factory){
    factory.add_enemy("bob", create_bob);
    factory.add_enemy("tank", create_tank);
}


extern "C" void register_towers(ITowerFactory& factory){
    factory.add_tower("Just tower", std::make_unique<GTowerNode>(create_simple_tower, 100, "assets/textures/entities/new_tower.png"));
    factory.add_tower("Magic tower", std::make_unique<GTowerNode>(create_magic_tower, 150, "assets/textures/entities/magic_tower.png"));
}

extern "C" void register_traps(ITrapFactory& factory){
    factory.add_trap("Mine", std::make_unique<GTrapNode>(create_simple_trap, 3, 70, 100, "assets/textures/entities/mine.png"));
    factory.add_trap("Magic trap", std::make_unique<GTrapNode>(create_magic_trap, 3 , 100, 150, "assets/textures/entities/magic_trap.png"));
}

extern "C" void register_effects(IEffectFactory& factory){
    factory.add_effect("poison", create_poisoning);
    factory.add_effect("weak", create_weakening);
    factory.add_effect("slow", create_slowdown);
}