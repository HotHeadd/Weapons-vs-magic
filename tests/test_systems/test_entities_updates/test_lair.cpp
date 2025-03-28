#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "update_fixtures.hpp"

TEST_F(UpdateTest, lair_move_point_node){
    LairNode node(1, 1);
    ASSERT_EQ(node.amount, 1);
    ASSERT_EQ(node.cooldown, 1);

    ASSERT_EQ(lair_ptr->spawn_point(), Coordinates(0, 1));

    lair_ptr->move(Coordinates(8, 9));
    ASSERT_EQ(lair_ptr->spawn_point(), Coordinates(7, 8));
}

TEST_F(UpdateTest, lair_update_wave_up){
    manager->get_system(SystemTag::ENEMY).remove(enemy_ptr);
    manager->get_system(SystemTag::ENEMY).remove(enemy_ptr_clone);
    ASSERT_TRUE(manager->get_enemies().empty());

    std::vector<std::unordered_map<std::string, LairNode>> wave_spawn_instrucitons;
    std::unordered_map<std::string, LairNode> first_wave;
    std::unordered_map<std::string, LairNode> second_wave;
    first_wave.emplace("bob", LairNode{1, 1});
    first_wave.emplace("tank", LairNode{1, 2});
    second_wave.emplace("bob", LairNode{1, 1});
    second_wave.emplace("tank", LairNode{1, 2});
    wave_spawn_instrucitons.push_back(first_wave);
    wave_spawn_instrucitons.push_back(second_wave);

    lair_ptr->add_spawn_instructions(wave_spawn_instrucitons);
    lair_ptr->spawn_instructions();

    lair_ptr->update();

    ASSERT_EQ(manager->get_enemies().size(), 0);

    lair_ptr->update();

    ASSERT_EQ(manager->get_enemies().size(), 1);

    lair_ptr->update();

    ASSERT_EQ(manager->get_enemies().size(), 2);
    ASSERT_TRUE(lair_ptr->no_enemies_left());

    lair_ptr->wave_up();
    ASSERT_FALSE(lair_ptr->no_enemies_left());
    lair_ptr->update();
    lair_ptr->update();
    lair_ptr->update();
    ASSERT_EQ(manager->get_enemies().size(), 4);
}