#include <gtest/gtest.h>
#include <memory>
#include "creators.hpp"
#include "enemy_factory.hpp"
#include "factories_fixtures.hpp"

using namespace WVM;

TEST(enemy_factory, create){
    MockManager manager;
    MockFactoryManager f_manager;
    EnemyFactory e_fac(manager, f_manager);
    e_fac.add_enemy("bob", create_bob);
    e_fac.add_enemy("tank", create_tank);

    ASSERT_TRUE(e_fac.can_create("bob"));
    ASSERT_FALSE(e_fac.can_create("antibob"));
    ASSERT_THROW(e_fac.add_enemy("bob", create_tank), std::runtime_error);
    ASSERT_THROW(e_fac.create("punk"), std::runtime_error);

    std::shared_ptr<IEnemy> bob_origninal = std::static_pointer_cast<IEnemy>(create_bob(manager, f_manager));
    std::shared_ptr<IEnemy> bob_factory = std::static_pointer_cast<IEnemy>(e_fac.create("bob"));
    std::shared_ptr<IEnemy> tank_factory = std::static_pointer_cast<IEnemy>(e_fac.create("tank"));

    ASSERT_EQ(bob_origninal->hp(), bob_factory->hp());
    ASSERT_EQ(bob_origninal->max_hp(), bob_factory->max_hp());
    ASSERT_EQ(bob_origninal->speed(), bob_factory->speed());
    ASSERT_EQ(bob_origninal->damage(), bob_factory->damage());
    ASSERT_EQ(bob_origninal->gold(), bob_factory->gold());
    ASSERT_EQ(bob_origninal->position(), bob_factory->position());

    ASSERT_NE(bob_factory->hp(), tank_factory->hp());

    ASSERT_EQ(tank_factory->hp(), 300);
}