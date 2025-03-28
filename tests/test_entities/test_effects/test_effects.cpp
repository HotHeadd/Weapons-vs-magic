#include <gtest/gtest.h>
#include "../mocks_and_fixtures.hpp"
#include "poisoning.hpp"
#include "weakening.hpp"
#include "slowdown.hpp"
#include <cmath>

TEST_F(EnemyTest, effects_set_duration){
    Poisoning poison(enemy_ptr, 7, 8);
    Weakening weaken(enemy_ptr, 5, 6);
    Slowdown slow(enemy_ptr, 1, 4);

    unsigned new_duration = 30;
    poison.set_duration(new_duration);
    weaken.set_duration(new_duration);
    slow.set_duration(new_duration);

    ASSERT_EQ(poison.turns_to_last(), new_duration);
    ASSERT_EQ(slow.turns_to_last(), new_duration);
    ASSERT_EQ(weaken.turns_to_last(), new_duration);
}

TEST_F(EnemyTest, effects_consturctors_setters){
    Poisoning poison(enemy_ptr);
    Poisoning poison_more(enemy_ptr, 7, 8);
    Weakening weaken(enemy_ptr);
    Weakening weaken_more(enemy_ptr, 7, 8);
    Slowdown slow(enemy_ptr);
    Slowdown slow_more(enemy_ptr, 7, 8);

    ASSERT_EQ(poison.strength(), 1);
    ASSERT_EQ(poison.turns_to_last(), 1);
    ASSERT_EQ(poison_more.strength(), 7);
    ASSERT_EQ(poison_more.turns_to_last(), 8);

    ASSERT_EQ(weaken.strength(), 1);
    ASSERT_EQ(weaken.turns_to_last(), 1);
    ASSERT_EQ(weaken_more.strength(), 7);
    ASSERT_EQ(weaken_more.turns_to_last(), 8);

    ASSERT_EQ(slow.strength(), 1);
    ASSERT_EQ(slow.turns_to_last(), 1);
    ASSERT_EQ(slow_more.strength(), 7);
    ASSERT_EQ(slow_more.turns_to_last(), 8);

    poison.set_strength(3);
    weaken.set_strength(3);
    slow.set_strength(3);

    ASSERT_EQ(poison.strength(), 3);
    ASSERT_EQ(weaken.strength(), 3);
    ASSERT_EQ(slow.strength(), 3);
}

TEST_F(EnemyTest, poison_inflict){
    unsigned strength = 2;
    Poisoning poison(enemy_ptr, strength, 16);
    poison.inflict();

    ASSERT_EQ(enemy_ptr->hp(), max_hp-strength*Poisoning::hp_per_tick);
    ASSERT_EQ(poison.turns_to_last(), Poisoning::tick_cooldown);

    for (int i=1; i<Poisoning::tick_cooldown; i++){
        poison.inflict();
        ASSERT_EQ(enemy_ptr->hp(), max_hp-strength*Poisoning::hp_per_tick);
        ASSERT_EQ(poison.turns_to_last(), Poisoning::tick_cooldown-i);
    }

    poison.inflict();
    
    ASSERT_EQ(enemy_ptr->hp(), max_hp-2*strength*Poisoning::hp_per_tick);
    ASSERT_EQ(poison.turns_to_last(), 0);
}

TEST_F(EnemyTest, weakening_inflict_neutralize){
    unsigned strength = 2;
    Weakening weak(enemy_ptr, strength, 3);

    weak.inflict();

    double mult = 1+Weakening::multiplier_addition*strength;
    ASSERT_EQ(enemy_ptr->damage_multiplier(), mult);

    hp_t damage = 10;
    enemy_ptr->take_damage(damage);
    ASSERT_EQ(enemy_ptr->hp(), max_hp-damage*mult);

    weak.inflict();
    ASSERT_EQ(enemy_ptr->damage_multiplier(), mult);

    weak.neutralize();
    ASSERT_EQ(enemy_ptr->damage_multiplier(), 1);
    weak.neutralize();
    ASSERT_EQ(enemy_ptr->damage_multiplier(), 1);
}

TEST_F(EnemyTest, slowdown_inflict_neutralize){
    unsigned strength = 2;
    Slowdown slow(enemy_ptr, strength, 3);

    ASSERT_EQ(enemy_ptr->speed(), speed);
    slow.inflict();

    ASSERT_EQ(enemy_ptr->speed(), speed*std::exp(-static_cast<double>(strength)*Slowdown::slow_coef));

    slow.inflict();
    ASSERT_EQ(enemy_ptr->speed(), speed*std::exp(-static_cast<double>(strength)*Slowdown::slow_coef));

    slow.neutralize();
    ASSERT_EQ(enemy_ptr->speed(), speed);
}