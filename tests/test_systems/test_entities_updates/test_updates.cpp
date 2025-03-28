#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "update_fixtures.hpp"

#include "magic_tower.hpp"
#include "effect_factory.hpp"
#include "creators.hpp"

TEST_F(UpdateTest, enemy_update){
    enemy_ptr->set_speed(500);
    Coordinates start{6, 1};
    enemy_ptr->move(start);
    manager->get_system(SystemTag::ENEMY).update();

    ASSERT_EQ(enemy_ptr->position(), start);
    manager->get_system(SystemTag::ENEMY).update();
    ASSERT_EQ(enemy_ptr->position(), start+Tile::DOWN);
    manager->get_system(SystemTag::ENEMY).update();
    ASSERT_EQ(enemy_ptr->position(), start+Tile::DOWN);
    manager->get_system(SystemTag::ENEMY).update();

    ASSERT_FALSE(manager->get_enemies().contains(enemy_ptr));
    ASSERT_EQ(manager->get_castle().hp(), castle_hp-e_damage);
    ASSERT_EQ(manager->get_castle().gold(), 0);
}

TEST_F(UpdateTest, tower_update_closeset){
    tower_ptr->set_rapidity(500);
    tower_ptr->set_strategy(Strategy::CLOSEST_TO_CASTLE);
    tower_ptr->update();

    EXPECT_EQ(enemy_ptr->hp(), e_max_hp);
    EXPECT_EQ(enemy_ptr_clone->hp(), e_max_hp-t_damage);

    tower_ptr->update();

    EXPECT_EQ(enemy_ptr->hp(), e_max_hp);
    ASSERT_EQ(enemy_ptr_clone->hp(), e_max_hp-2*t_damage);
}

TEST_F(UpdateTest, tower_reset){
    tower_ptr->set_rapidity(500);
    tower_ptr->set_strategy(Strategy::CLOSEST_TO_CASTLE);

    tower_ptr->reset_cooldown();
    tower_ptr->update();

    EXPECT_EQ(enemy_ptr->hp(), e_max_hp);
    ASSERT_EQ(enemy_ptr_clone->hp(), e_max_hp-t_damage);
}

TEST_F(UpdateTest, tower_farthest){
    tower_ptr->set_rapidity(1000);
    tower_ptr->set_strategy(Strategy::FARTHEST_FROM_CASTLE);

    tower_ptr->update();

    EXPECT_EQ(enemy_ptr->hp(), e_max_hp-t_damage);
    ASSERT_EQ(enemy_ptr_clone->hp(), e_max_hp);
}

TEST_F(UpdateTest, tower_stongest){
    enemy_ptr->move(Coordinates{2, 2});
    enemy_ptr_clone->take_damage(1);
    tower_ptr->set_rapidity(1000);
    tower_ptr->set_strategy(Strategy::HEALTHIEST);

    tower_ptr->update();

    EXPECT_EQ(enemy_ptr->hp(), e_max_hp-t_damage);
    ASSERT_EQ(enemy_ptr_clone->hp(), e_max_hp-1);
}

TEST_F(UpdateTest, tower_weakest){
    enemy_ptr->move(Coordinates{2, 2});
    enemy_ptr_clone->take_damage(1);
    tower_ptr->set_rapidity(1000);
    tower_ptr->set_strategy(Strategy::WEAKEST);

    tower_ptr->update();

    EXPECT_EQ(enemy_ptr->hp(), e_max_hp);
    ASSERT_EQ(enemy_ptr_clone->hp(), e_max_hp-t_damage-1);
}

TEST_F(UpdateTest, tower_fastest){
    enemy_ptr->move(Coordinates{2, 2});
    enemy_ptr_clone->set_speed(e_speed+2);
    tower_ptr->set_rapidity(1000);
    tower_ptr->set_strategy(Strategy::FASTEST);

    tower_ptr->update();

    EXPECT_EQ(enemy_ptr->hp(), e_max_hp);
    ASSERT_EQ(enemy_ptr_clone->hp(), e_max_hp-t_damage);
}

TEST_F(UpdateTest, magic_tower){
    EffectFactory factory;
    factory.add_effect("poison", create_poisoning);
    std::unordered_map<std::string, MagicNode> effects;
    effects.emplace("poison", MagicNode{1, 1});
    MagicTower magic_tower(
        *manager,
        factory,
        t_max_hp,
        t_pos,
        t_cost,
        t_vision,
        t_damage,
        t_rapidity,
        t_levelup_rules,
        effects
    );
    magic_tower.set_rapidity(1000);
    magic_tower.move(Coordinates{1, 2});
    enemy_ptr->move(Coordinates{0, 2});
    enemy_ptr_clone->move(Coordinates{2, 2});

    magic_tower.update();

    ASSERT_TRUE(enemy_ptr->effects().empty());
    ASSERT_FALSE(enemy_ptr_clone->effects().empty());

    manager->get_system(SystemTag::ENEMY).update();

    ASSERT_EQ(enemy_ptr->hp(), e_max_hp);
    ASSERT_NE(enemy_ptr_clone->hp(), e_max_hp);
}