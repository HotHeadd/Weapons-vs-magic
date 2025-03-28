#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../mocks_and_fixtures.hpp"
#include "enemy.hpp"

TEST(enemy, constructor){
    MockManager manager;
    Coordinates coords(0, 0);
    hp_t max_hp = 10;
    double speed = 3;
    unsigned damage = 3;
    unsigned gold = 10;

    Enemy enemy(manager, max_hp, speed, damage, gold, coords);

    ASSERT_EQ(enemy.gold(), gold);
    ASSERT_EQ(enemy.damage(), damage);
    ASSERT_EQ(enemy.speed(), speed);
    ASSERT_EQ(enemy.max_hp(), max_hp);
    ASSERT_EQ(enemy.hp(), max_hp);
    ASSERT_EQ(enemy.position(), coords);
    ASSERT_EQ(enemy.damage_multiplier(), 1);
    ASSERT_EQ(enemy.healing_multiplier(), 1);
}

TEST(enemy, setters){
    MockManager manager;
    unsigned new_speed = 10;
    hp_t new_max_hp = 100;
    double new_mult = 1.2;
    Coordinates new_position(10, 10);
    Enemy enemy(manager, 1, 1, 1, 1, {1, 1});

    enemy.set_speed(new_speed);
    enemy.set_damage_multiplier(new_mult);
    enemy.set_healing_multiplier(new_mult);
    enemy.set_max_hp(new_max_hp);
    enemy.move(new_position);
    
    ASSERT_EQ(enemy.speed(), new_speed);
    ASSERT_EQ(enemy.max_hp(), new_max_hp);
    ASSERT_EQ(enemy.damage_multiplier(), new_mult);
    ASSERT_EQ(enemy.healing_multiplier(), new_mult);
    ASSERT_EQ(enemy.position(), new_position);
}

TEST(enemy, heal){
    MockManager manager;
    Enemy enemy(manager, 1, 1, 1, 1 , {1, 1});
    enemy.set_max_hp(100);
    enemy.restore_hp(10);

    ASSERT_EQ(enemy.hp(), 11);

    enemy.restore_hp(1000);

    ASSERT_EQ(enemy.hp(), enemy.max_hp());
}

TEST(enemy, take_damage){
    MockManager manager;
    hp_t max_hp = 100;
    Enemy enemy(manager, max_hp, 1, 1, 1 , {1, 1});
    Enemy enemy_clone(manager, max_hp, 1, 1, 1 , {1, 1});
    double clone_damage_multiplier = 1.5;
    hp_t damage_amount = 10;

    enemy_clone.set_damage_multiplier(clone_damage_multiplier);

    enemy.take_damage(damage_amount);
    enemy_clone.take_damage(damage_amount);

    ASSERT_EQ(enemy.hp(), max_hp-damage_amount);
    ASSERT_EQ(enemy_clone.hp(), max_hp-damage_amount*clone_damage_multiplier);

    enemy.restore_hp(damage_amount);
    enemy_clone.restore_hp(damage_amount);

    ASSERT_EQ(enemy.hp(), enemy.max_hp());
    ASSERT_NE(enemy_clone.hp(), enemy_clone.max_hp());
}

TEST(enemy, restore_hp){
    MockManager manager;
    hp_t max_hp = 100;
    Enemy enemy(manager, max_hp, 1, 1, 1 , {1, 1});
    Enemy enemy_clone(manager, max_hp, 1, 1, 1 , {1, 1});
    double clone_healing_multiplier = 1.5;
    enemy_clone.set_healing_multiplier(clone_healing_multiplier);

    enemy.take_damage(max_hp/2);
    enemy_clone.take_damage(max_hp/2);

    enemy.restore_hp(max_hp/4);
    enemy_clone.restore_hp(max_hp/4);

    ASSERT_EQ(enemy.hp(), max_hp*3/4);
    ASSERT_EQ(enemy_clone.hp(), max_hp*(2+clone_healing_multiplier)/4);
}

TEST_F(EnemyTest, test_distance_and_coordinates){
    Enemy enemy(manager, max_hp, 1, 1, 1 , {1, 1});

    ASSERT_EQ(distance(enemy, *enemy_ptr), sqrt(pow(6, 2) + pow(7, 2)));

    Coordinates expected = {8, 9};
    ASSERT_EQ(enemy.position() + enemy_ptr->position(), expected);
}