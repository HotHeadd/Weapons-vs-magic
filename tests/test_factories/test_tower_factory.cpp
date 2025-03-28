#include <gtest/gtest.h>
#include <memory>
#include "creators.hpp"
#include "factory_manager.hpp"
#include "factories_fixtures.hpp"
#include "tower.hpp"
#include "magic_tower.hpp"

using namespace WVM;

TEST(tower_factory, create){
    MockManager manager;
    FactoryManager f_manager(manager);

    TowerFactory& t_fac = static_cast<TowerFactory&>(f_manager.get_tower_factory());
    t_fac.add_tower("simple", std::make_unique<TowerNode>(create_simple_tower, 100));
    t_fac.add_tower("magic", std::make_unique<TowerNode>(create_magic_tower, 200));

    ASSERT_TRUE(t_fac.can_create("simple"));
    ASSERT_TRUE(t_fac.can_create("magic"));
    ASSERT_EQ(t_fac.get_cost("simple"), 100);
    ASSERT_EQ(t_fac.get_cost("magic"), 200);

    ASSERT_THROW(t_fac.add_tower("magic", std::make_unique<TowerNode>(create_magic_tower, 100)), std::runtime_error);
    ASSERT_THROW(t_fac.create("punk"), std::runtime_error);

    auto assist_node = std::make_unique<TowerNode>(create_simple_tower, 100);
    auto assist_node_for_magic = std::make_unique<TowerNode>(create_magic_tower, 200);
    std::shared_ptr<Tower> t_orig = std::static_pointer_cast<Tower>(create_simple_tower(manager, f_manager, *assist_node));
    std::shared_ptr<Tower> t_fact = std::static_pointer_cast<Tower>(f_manager.get_tower_factory().create("simple"));

    std::shared_ptr<MagicTower> magic_tower = std::static_pointer_cast<MagicTower>(f_manager.get_tower_factory().create("magic"));
    std::shared_ptr<MagicTower> magic_tower_orig = std::static_pointer_cast<MagicTower>(create_magic_tower(manager, f_manager, *assist_node_for_magic));

    ASSERT_EQ(t_orig->hp(), t_fact->hp());
    ASSERT_EQ(t_orig->shot_damage(), t_fact->shot_damage());
    ASSERT_EQ(t_orig->vision_radius(), t_fact->vision_radius());

    ASSERT_EQ(magic_tower->hp(), magic_tower_orig->hp());
    ASSERT_EQ(magic_tower->magic_effects().size(), magic_tower_orig->magic_effects().size());
    ASSERT_EQ(magic_tower->cost(), magic_tower_orig->cost());

}