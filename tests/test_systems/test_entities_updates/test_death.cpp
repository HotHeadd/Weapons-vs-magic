#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "update_fixtures.hpp"

TEST_F(UpdateTest, enemy_death){
    enemy_ptr->take_damage(e_max_hp);
    ASSERT_FALSE(manager->get_enemies().empty());
    manager->get_system(SystemTag::ENEMY).update();

    ASSERT_FALSE(manager->get_enemies().contains(enemy_ptr));
}

TEST_F(UpdateTest, tower_sell){
    ASSERT_FALSE(manager->get_defence().empty());
    ASSERT_TRUE(manager->get_defence().contains(tower_ptr));

    manager->get_system(SystemTag::DEFENCE).update();
    ASSERT_FALSE(manager->get_defence().empty());

    tower_ptr->sell();

    ASSERT_EQ(manager->get_castle().gold(), t_cost/2);
    ASSERT_TRUE(tower_ptr->is_dead());

    manager->get_system(SystemTag::DEFENCE).update();

    ASSERT_TRUE(manager->get_defence().empty());
}

TEST_F(UpdateTest, tower_death){
    ASSERT_FALSE(manager->get_defence().empty());

    tower_ptr->take_damage(t_max_hp);
    ASSERT_TRUE(tower_ptr->is_dead());

    manager->get_system(SystemTag::DEFENCE).update();

    ASSERT_EQ(manager->get_castle().gold(), 0);
    ASSERT_TRUE(manager->get_defence().empty());
}