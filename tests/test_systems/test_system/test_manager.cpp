#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "system_manager.hpp"
#include "system_fixtures.hpp"

using namespace WVM;

TEST(system_manager, constructor){
    std::shared_ptr<Layout> layout = std::make_shared<Layout>(5, 5);
    std::shared_ptr<Castle> castle = std::make_shared<Castle>(100);
    SystemManager manager(layout, castle);

    ASSERT_EQ(&(manager.get_layout()), layout.get());
    ASSERT_EQ(manager.get_castle().hp(), castle->hp());

    int i=0;
    for (auto& system : manager){
        ++i;
    }
    ASSERT_EQ(i, 4);
}

TEST_F(ManagerTest, getters){
    std::shared_ptr<MockEnemy> enemy = std::make_shared<MockEnemy>();
    std::shared_ptr<MockDefence> defence = std::make_shared<MockDefence>();
    manager->get_system(SystemTag::ENEMY).add(enemy);
    manager->get_system(SystemTag::DEFENCE).add(defence);
    std::unordered_set<std::shared_ptr<IEnemy>>& enemies = manager->get_enemies();
    std::unordered_set<std::shared_ptr<IDefence>>& defence_set = manager->get_defence();

    ASSERT_EQ(enemies.size(), 1);
    ASSERT_EQ(defence_set.size(), 1);

    ASSERT_TRUE(enemies.contains(enemy));
    ASSERT_TRUE(defence_set.contains(defence));
}