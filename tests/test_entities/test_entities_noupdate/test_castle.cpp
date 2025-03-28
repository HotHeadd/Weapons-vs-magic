#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "castle.hpp"

using namespace WVM;

TEST(castle, constructor){
    hp_t max_hp = 100;
    Castle castle(max_hp);
    Castle castle_more(max_hp);

    ASSERT_EQ(castle.gold(), 0);
    ASSERT_TRUE(castle.is_alive());
    ASSERT_EQ(castle.max_hp(), max_hp);
    ASSERT_EQ(castle.hp(), max_hp);

    ASSERT_EQ(castle_more.gold(), 0);
    ASSERT_TRUE(castle_more.is_alive());
    ASSERT_EQ(castle_more.max_hp(), max_hp);
    ASSERT_EQ(castle_more.hp(), max_hp);
}

TEST(castle, gold){
    Castle castle(100);

    castle.increase_gold(50);

    ASSERT_EQ(castle.gold(), 50);
    ASSERT_TRUE(castle.enough(30));

    castle.decrease_gold(30);
    ASSERT_EQ(castle.gold(), 20);
    ASSERT_FALSE(castle.enough(30));

    castle.decrease_gold(30);
    ASSERT_EQ(castle.gold(), 0);
}

TEST(castle, damage){
    Castle castle(100);

    castle.take_damage(60);

    ASSERT_TRUE(castle.is_alive());
    ASSERT_EQ(castle.hp(), 40);

    castle.take_damage(50);

    ASSERT_FALSE(castle.is_alive());
    ASSERT_EQ(castle.hp(), -10);
}