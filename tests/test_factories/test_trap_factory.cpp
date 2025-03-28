#include <gtest/gtest.h>
#include <memory>
#include "creators.hpp"
#include "factory_manager.hpp"
#include "factories_fixtures.hpp"
#include "trap.hpp"
#include "magic_trap.hpp"

TEST(trap_factory, create){
    MockManager manager;
    FactoryManager f_manager(manager);
    TrapNode node_for_test_coverage_beautiful;

    TrapFactory& t_fac = static_cast<TrapFactory&>(f_manager.get_trap_factory());
    unsigned t_max_level = 2, t_cost = 100, t_levelup_cost = 150;
    unsigned mg_max_level=2, mg_cost = 300, mg_levelup_cost = 450;
    std::make_unique<TrapNode>(create_magic_trap, mg_max_level, mg_cost, mg_levelup_cost);
    t_fac.add_trap("simple", std::make_unique<TrapNode>(create_simple_trap, t_max_level, t_cost, t_levelup_cost));
    t_fac.add_trap("magic", std::make_unique<TrapNode>(create_magic_trap, mg_max_level, mg_cost, mg_levelup_cost));

    ASSERT_TRUE(t_fac.can_create("simple"));
    ASSERT_TRUE(t_fac.can_create("magic"));
    ASSERT_FALSE(t_fac.can_create("boolean"));
    ASSERT_EQ(t_fac.get_cost("simple"), t_cost);
    ASSERT_EQ(t_fac.get_cost("magic"), mg_cost);
    ASSERT_EQ(t_fac.get_level("simple"), 1);
    ASSERT_EQ(t_fac.get_level("magic"), 1);
    ASSERT_EQ(t_fac.get_levelup_cost("simple"), t_levelup_cost);
    ASSERT_EQ(t_fac.get_levelup_cost("magic"), mg_levelup_cost);
    ASSERT_EQ(t_fac.get_max_level("simple"), t_max_level);
    ASSERT_EQ(t_fac.get_max_level("magic"), mg_max_level);

    ASSERT_THROW(t_fac.add_trap("simple", std::make_unique<TrapNode>(create_simple_trap,1, 1, 1));, std::runtime_error);
    ASSERT_THROW(t_fac.create("punk"), std::runtime_error);
    ASSERT_THROW(t_fac.get_cost("bool"), std::runtime_error);
    ASSERT_THROW(t_fac.get_levelup_cost("bool"), std::runtime_error);
    ASSERT_THROW(t_fac.get_max_level("bool"), std::runtime_error);
    ASSERT_THROW(t_fac.get_level("bool"), std::runtime_error);

    std::shared_ptr<Trap> s_tower1 = std::static_pointer_cast<Trap>(t_fac.create("simple"));
    std::shared_ptr<MagicTrap> m_tower1 = std::static_pointer_cast<MagicTrap>(t_fac.create("magic"));

    t_fac.levelup_trap("simple");
    t_fac.levelup_trap("magic");
    ASSERT_EQ(t_fac.get_level("simple"), 2);
    ASSERT_EQ(t_fac.get_level("magic"), 2);
    ASSERT_EQ(t_fac.get_levelup_cost("simple"), t_levelup_cost*1.5);
    ASSERT_EQ(t_fac.get_levelup_cost("magic"), mg_levelup_cost*1.5);
    ASSERT_THROW(t_fac.levelup_trap("bool"), std::runtime_error);
    ASSERT_THROW(t_fac.levelup_trap("magic"), std::runtime_error);

    std::shared_ptr<Trap> s_tower2 = std::static_pointer_cast<Trap>(t_fac.create("simple"));
    std::shared_ptr<MagicTrap> m_tower2 = std::static_pointer_cast<MagicTrap>(t_fac.create("magic"));

    ASSERT_EQ(s_tower1->shot_damage(), s_tower2->shot_damage()-5);
    ASSERT_EQ(s_tower1->vision_radius(), s_tower2->vision_radius()-1);
    ASSERT_EQ(s_tower1->cost(), s_tower2->cost()-50);

    ASSERT_EQ(m_tower1->shot_damage(), m_tower2->shot_damage()-5);
    ASSERT_EQ(m_tower1->vision_radius(), m_tower2->vision_radius()-1);
    ASSERT_EQ(m_tower1->cost(), m_tower2->cost()-50);
    ASSERT_EQ(m_tower1->magic_effects().size(), m_tower2->magic_effects().size()-1);
}