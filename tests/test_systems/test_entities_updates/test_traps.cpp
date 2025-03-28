#include <gtest/gtest.h>

#include "trap.hpp"
#include "magic_trap.hpp"
#include "update_fixtures.hpp"
#include "effect_factory.hpp"
#include "creators.hpp"

TEST_F(UpdateTest, trap){
    double trap_vision = 2, trap_radius = 3;
    Trap trap(
        *manager,
        Coordinates(2, 5),
        t_cost,
        trap_vision,
        trap_radius,
        t_damage
    );
    enemy_ptr->move({0, 0});
    enemy_ptr_clone->move({5, 5});

    trap.update();

    ASSERT_EQ(enemy_ptr->hp(), e_max_hp);
    ASSERT_EQ(enemy_ptr_clone->hp(), e_max_hp);
    ASSERT_FALSE(trap.is_dead());

    enemy_ptr->move({2, 3});

    trap.update();

    ASSERT_EQ(enemy_ptr->hp(), e_max_hp-t_damage);
    ASSERT_EQ(enemy_ptr_clone->hp(), e_max_hp-t_damage);
    ASSERT_TRUE(trap.is_dead());

    enemy_ptr_clone->move({9, 9});
    trap.update();
    ASSERT_EQ(enemy_ptr->hp(), e_max_hp-2*t_damage);
    ASSERT_EQ(enemy_ptr_clone->hp(), e_max_hp-t_damage);
}

TEST_F(UpdateTest, magic_trap){
    EffectFactory factory;
    factory.add_effect("poison", create_poisoning);
    std::unordered_map<std::string, MagicNode> effects;
    effects.emplace("poison", MagicNode{1, 1});
    double trap_vision = 2, trap_radius = 3;
    MagicTrap trap(
        *manager,
        factory,
        Coordinates{2, 5},
        t_cost,
        trap_vision,
        trap_radius,
        t_damage,
        effects
    );

    enemy_ptr->move({0, 0});
    enemy_ptr_clone->move({5, 5});

    trap.update();

    ASSERT_EQ(enemy_ptr->hp(), e_max_hp);
    ASSERT_EQ(enemy_ptr_clone->hp(), e_max_hp);
    ASSERT_FALSE(trap.is_dead());

    enemy_ptr->move({2, 3});

    trap.update();

    ASSERT_EQ(enemy_ptr->hp(), e_max_hp-t_damage);
    ASSERT_EQ(enemy_ptr->effects().size(), 1);
    ASSERT_EQ(enemy_ptr_clone->hp(), e_max_hp-t_damage);
    ASSERT_EQ(enemy_ptr_clone->effects().size(), 1);
    ASSERT_TRUE(trap.is_dead());

    enemy_ptr_clone->move({9, 9});
    trap.update();
    EXPECT_EQ(enemy_ptr->hp(), e_max_hp-2*t_damage);
    EXPECT_EQ(enemy_ptr->effects().size(), 2);
    EXPECT_EQ(enemy_ptr_clone->hp(), e_max_hp-t_damage);
    EXPECT_EQ(enemy_ptr_clone->effects().size(), 1);
}