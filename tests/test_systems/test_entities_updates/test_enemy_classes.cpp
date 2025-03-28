#include <gtest/gtest.h>

#include "update_fixtures.hpp"
#include "healing_enemy.hpp"
#include "shooting_enemy.hpp"

TEST_F(UpdateTest, update_healing){
    double vision_radius = 3;
    hp_t healing_amount = 10;
    double healing_speed = 1000;
    std::shared_ptr<HealingEnemy> h_enemy = std::make_shared<HealingEnemy>(
        *manager,
        e_max_hp,
        e_speed,
        e_damage,
        e_gold,
        Coordinates(0, 5),
        vision_radius,
        healing_speed,
        healing_amount
    );
    h_enemy->move({2, 4});
    enemy_ptr->move({2, 6});
    enemy_ptr_clone->move({2, 0});

    enemy_ptr->take_damage(15);
    enemy_ptr_clone->take_damage(15);
    h_enemy->update();

    ASSERT_EQ(enemy_ptr->hp(), e_max_hp-5);
    ASSERT_EQ(enemy_ptr_clone->hp(), e_max_hp-15);

    enemy_ptr_clone->move({2, 3});
    h_enemy->update();
    ASSERT_EQ(enemy_ptr->hp(), e_max_hp);
    ASSERT_EQ(enemy_ptr_clone->hp(), e_max_hp-5);
}

TEST_F(UpdateTest, update_shooting){
    double vision_radius = 3;
    hp_t shot_damage = 10;
    double rapidity = 1000;
    std::shared_ptr<ShootingEnemy> s_enemy = std::make_shared<ShootingEnemy>(
        *manager,
        e_max_hp,
        e_speed,
        e_damage,
        e_gold,
        Coordinates(0, 5),
        vision_radius,
        rapidity,
        shot_damage
    );
    std::shared_ptr<Tower> tower_ptr_clone = std::make_shared<Tower>(
        *manager, 
        t_max_hp,
        t_pos,
        t_cost,
        t_vision,
        t_damage,
        t_rapidity,
        t_levelup_rules);
    manager->get_system(SystemTag::DEFENCE).add(tower_ptr_clone);
    s_enemy->move({2, 4});
    tower_ptr_clone->move({9, 9});
    s_enemy->update();

    EXPECT_EQ(tower_ptr->hp(), t_max_hp-shot_damage);
    EXPECT_EQ(tower_ptr_clone->hp(), t_max_hp);

    tower_ptr_clone->move({2, 3});

    s_enemy->update();

    EXPECT_EQ(tower_ptr->hp(), t_max_hp-shot_damage);
    EXPECT_EQ(tower_ptr_clone->hp(), t_max_hp-shot_damage);

    s_enemy->set_vision(1.11);
    s_enemy->set_shot_damage(1.22);

    ASSERT_EQ(s_enemy->vision_radius(), 1.11);
    ASSERT_EQ(s_enemy->shot_damage(), 1.22);
}