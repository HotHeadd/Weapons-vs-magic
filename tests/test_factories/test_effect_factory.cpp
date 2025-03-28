#include <gtest/gtest.h>
#include <memory>
#include "effect_factory.hpp"
#include "creators.hpp"
#include "enemy.hpp"
#include "factories_fixtures.hpp"

using namespace WVM;

TEST(effect_factory, create){
    MockManager manager;
    MockFactoryManager f_manager;
    EffectFactory effect_fac;
    effect_fac.add_effect("poison", create_poisoning);
    effect_fac.add_effect("weakening", create_weakening);
    effect_fac.add_effect("slowdown", create_slowdown);

    ASSERT_THROW(effect_fac.add_effect("poison", create_poisoning), std::runtime_error);
    ASSERT_TRUE(effect_fac.can_create("poison"));
    ASSERT_TRUE(effect_fac.can_create("weakening"));
    ASSERT_TRUE(effect_fac.can_create("slowdown"));
    ASSERT_FALSE(effect_fac.can_create("empower"));

    std::shared_ptr<Enemy> enemy = std::static_pointer_cast<Enemy>(create_bob(manager, f_manager));
    std::shared_ptr<Effect> weak_factory = effect_fac.create("weakening", enemy);
    std::shared_ptr<Effect> weak_original = effect_fac.create("weakening", enemy);

    ASSERT_THROW(effect_fac.create("empower", enemy), std::runtime_error);
    ASSERT_EQ(weak_factory->strength(), weak_original->strength());
    ASSERT_EQ(weak_factory->turns_to_last(), weak_original->turns_to_last());
}