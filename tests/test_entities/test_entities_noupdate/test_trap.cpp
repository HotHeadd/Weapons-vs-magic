#include <gtest/gtest.h>
#include "../mocks_and_fixtures.hpp"
#include "trap.hpp"
#include "magic_trap.hpp"
#include "effect_factory.hpp"

TEST(trap, constructor_setters){
    unsigned cost = 3;
    double vision = 4, effect_r = 5, damage = 10;
    MockManager manager;
    Trap trap(
        manager,
        Coordinates{1, 1},
        cost,
        vision,
        effect_r,
        damage
    );

    ASSERT_EQ(trap.cost(), cost);
    ASSERT_EQ(trap.shot_damage(), damage);
    ASSERT_EQ(trap.vision_radius(), vision);
    ASSERT_EQ(trap.effect_radius(), effect_r);
    ASSERT_FALSE(trap.is_dead());

    trap.set_shot_damage(20);
    trap.set_vision(30);
    ASSERT_EQ(trap.shot_damage(),20);
    ASSERT_EQ(trap.vision_radius(), 30);

    trap.reset_cooldown();
    trap.on_death();
}

TEST(magic_trap, constructor){
    EffectFactory factory;
    std::unordered_map<std::string, MagicNode> effects;
    MockManager manager;
    unsigned cost = 3;
    double vision = 4, effect_r = 5, damage = 10;
    MagicTrap trap(
        manager,
        factory,
        Coordinates{1, 1},
        cost,
        vision,
        effect_r,
        damage,
        effects
    );

    ASSERT_EQ(trap.cost(), cost);
    ASSERT_EQ(trap.shot_damage(), damage);
    ASSERT_EQ(trap.vision_radius(), vision);
    ASSERT_EQ(trap.effect_radius(), effect_r);
    ASSERT_FALSE(trap.is_dead());
}