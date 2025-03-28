#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "system_fixtures.hpp"
#include "system_manager.hpp"
#include "enemy_system.hpp"
#include "defence_system.hpp"
#include "effect_system.hpp"
#include "lair_system.hpp"

using ::testing::Return;

TEST_F(ManagerTest, enemy_system){
    std::shared_ptr<MockEnemy> enemy1 = std::make_shared<MockEnemy>();
    std::shared_ptr<MockEnemy> enemy2 = std::make_shared<MockEnemy>();
    std::shared_ptr<MockDefence> defence = std::make_shared<MockDefence>();

    EnemySystem& e_system = dynamic_cast<EnemySystem&>(manager->get_system(SystemTag::ENEMY));

    e_system.add(enemy1);
    e_system.add(enemy2);

    ASSERT_THROW(e_system.add(defence), std::runtime_error);
    ASSERT_THROW(e_system.add(enemy1), std::runtime_error);
    ASSERT_TRUE(e_system.get_enemies().contains(enemy1));
    ASSERT_TRUE(e_system.get_enemies().contains(enemy2));

    e_system.remove(enemy2);

    ASSERT_FALSE(e_system.get_enemies().contains(enemy2));
    ASSERT_THROW(e_system.remove(defence), std::runtime_error);
    ASSERT_THROW(e_system.remove(enemy2), std::runtime_error);

    e_system.remove(enemy1);
    ASSERT_FALSE(e_system.get_enemies().contains(enemy2));
    ASSERT_TRUE(e_system.is_empty());
}

TEST_F(ManagerTest, defence_system){
    std::shared_ptr<MockDefence> defence1 = std::make_shared<MockDefence>();
    std::shared_ptr<MockDefence> defence2 = std::make_shared<MockDefence>();
    std::shared_ptr<MockEnemy> enemy = std::make_shared<MockEnemy>();

    DefenceSystem& d_system = dynamic_cast<DefenceSystem&>(manager->get_system(SystemTag::DEFENCE));

    d_system.add(defence1);
    d_system.add(defence2);

    EXPECT_CALL(*defence1, update());
    EXPECT_CALL(*defence2, update());
    EXPECT_CALL(*defence1, reset_cooldown());
    EXPECT_CALL(*defence2, reset_cooldown());
    d_system.update();
    d_system.refresh();

    ASSERT_THROW(d_system.add(enemy), std::runtime_error);
    ASSERT_THROW(d_system.add(defence1), std::runtime_error);
    ASSERT_TRUE(d_system.get_defence().contains(defence1));
    ASSERT_TRUE(d_system.get_defence().contains(defence2));

    d_system.remove(defence2);

    ASSERT_FALSE(d_system.get_defence().contains(defence2));
    ASSERT_THROW(d_system.remove(enemy), std::runtime_error);
    ASSERT_THROW(d_system.remove(defence2), std::runtime_error);

    d_system.remove(defence1);
    ASSERT_FALSE(d_system.get_defence().contains(defence2));
    ASSERT_TRUE(d_system.get_defence().empty());
}

TEST_F(ManagerTest, effect_system){
    std::shared_ptr<MockEnemy> enemy1 = std::make_shared<MockEnemy>();
    std::shared_ptr<MockEnemy> enemy2 = std::make_shared<MockEnemy>();
    std::shared_ptr<MockEnemy> enemy3 = std::make_shared<MockEnemy>();

    EXPECT_CALL(*enemy1, inflict_effects()).Times(1);
    EXPECT_CALL(*enemy2, inflict_effects()).Times(1);
    EXPECT_CALL(*enemy3, inflict_effects()).Times(2);
    EXPECT_CALL(*enemy1, vanish_effects()).Times(1);
    EXPECT_CALL(*enemy2, vanish_effects()).Times(1);
    EXPECT_CALL(*enemy3, vanish_effects()).Times(1);

    EffectSystem& e_system = dynamic_cast<EffectSystem&>(manager->get_system(SystemTag::EFFECT));

    e_system.add(enemy1);
    e_system.add(enemy2);
    e_system.add(enemy3);
    e_system.update();
    e_system.refresh();
    e_system.remove(enemy1);
    ASSERT_THROW(e_system.remove(enemy1), std::runtime_error);
    enemy2.reset();
    ASSERT_THROW(e_system.remove(enemy2), std::runtime_error);
    e_system.update();
    enemy3.reset();
    e_system.update();
}

TEST_F(ManagerTest, effect_system_defence){
    std::shared_ptr<MockDefence> defence1 = std::make_shared<MockDefence>();
    std::shared_ptr<MockDefence> defence2 = std::make_shared<MockDefence>();
    std::shared_ptr<MockDefence> defence3 = std::make_shared<MockDefence>();

    EXPECT_CALL(*defence1, inflict_effects());
    EXPECT_CALL(*defence2, inflict_effects());
    EXPECT_CALL(*defence3, inflict_effects()).Times(2);
    EXPECT_CALL(*defence1, vanish_effects());
    EXPECT_CALL(*defence2, vanish_effects());
    EXPECT_CALL(*defence3, vanish_effects());

    EffectSystem& e_system = dynamic_cast<EffectSystem&>(manager->get_system(SystemTag::EFFECT));

    e_system.add(defence1);
    e_system.add(defence2);
    e_system.add(defence3);
    e_system.update();
    e_system.refresh();
    e_system.remove(defence1);
    ASSERT_THROW(e_system.remove(defence1), std::runtime_error);
    defence2.reset();
    ASSERT_THROW(e_system.remove(defence2), std::runtime_error);
    e_system.update();
    defence3.reset();
    e_system.update();
}

TEST_F(ManagerTest, lair_system){
    std::shared_ptr<MockLair> lair1 = std::make_shared<MockLair>();
    std::shared_ptr<MockLair> lair2 = std::make_shared<MockLair>();

    EXPECT_CALL(*lair1, update()).Times(2);
    EXPECT_CALL(*lair2, update()).Times(1);
    EXPECT_CALL(*lair1, wave_up()).Times(1);
    EXPECT_CALL(*lair2, wave_up()).Times(1);

    EXPECT_CALL(*lair1, no_enemies_left()).WillRepeatedly(Return(true));
    EXPECT_CALL(*lair2, no_enemies_left()).WillRepeatedly(Return(false));

    EXPECT_CALL(*lair2, on_death());

    LairSystem& l_system = dynamic_cast<LairSystem&>(manager->get_system(SystemTag::LAIR));

    l_system.add(lair1);

    ASSERT_TRUE(l_system.is_empty());
    ASSERT_THROW(l_system.add(lair1),std::runtime_error);

    l_system.add(lair2);

    ASSERT_FALSE(l_system.is_empty());

    l_system.update();
    l_system.refresh();

    l_system.remove(lair2);
    ASSERT_THROW(l_system.remove(lair2),std::runtime_error);

    ASSERT_TRUE(l_system.is_empty());
    l_system.update();
}