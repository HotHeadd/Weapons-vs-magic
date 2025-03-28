#include <gtest/gtest.h>
#include "poisoning.hpp"
#include "weakening.hpp"
#include "slowdown.hpp"
#include "magic.hpp"
#include <cmath>

#include "../mocks_and_fixtures.hpp"

TEST_F(EffectTest, effected_add_remove){
    std::shared_ptr<Poisoning> poison =  std::make_shared<Poisoning>(enemy_ptr);
    enemy_ptr->add_effect(poison);
    ASSERT_THROW(enemy_ptr->add_effect(poison), std::runtime_error);

    ASSERT_TRUE(enemy_ptr->effects().contains(poison));
    ASSERT_EQ(enemy_ptr->effects().size(), 1);

    enemy_ptr->remove_effect(poison);

    ASSERT_FALSE(enemy_ptr->effects().contains(poison));
    ASSERT_TRUE(enemy_ptr->effects().empty());
    ASSERT_THROW(enemy_ptr->remove_effect(poison), std::runtime_error);
}

TEST_F(EffectTest, vanish_effects){
    enemy_ptr->add_effect(factory->create("poison", enemy_ptr));
    enemy_ptr->add_effect(factory->create("poison", enemy_ptr));
    enemy_ptr->add_effect(factory->create("poison", enemy_ptr));
    enemy_ptr->add_effect(factory->create("poison", enemy_ptr));
    enemy_ptr->add_effect(factory->create("poison", enemy_ptr));

    ASSERT_EQ(enemy_ptr->effects().size(), 5);

    enemy_ptr->vanish_effects();

    ASSERT_TRUE(enemy_ptr->effects().empty());
}

TEST_F(EffectTest, inflict){
    enemy_ptr->add_effect(factory->create("poison", enemy_ptr));
    enemy_ptr->add_effect(factory->create("poison", enemy_ptr));
    enemy_ptr->add_effect(factory->create("poison", enemy_ptr));
    enemy_ptr->add_effect(factory->create("poison", enemy_ptr));
    enemy_ptr->add_effect(factory->create("poison", enemy_ptr));

    enemy_ptr->inflict_effects();

    ASSERT_EQ(enemy_ptr->hp(), max_hp - 5*Poisoning::hp_per_tick);
    std::unordered_set<std::shared_ptr<Effect>>& effects = enemy_ptr->effects();
    for (auto& effect : effects){
        ASSERT_EQ(effect->turns_to_last(), 0);
    }
    
    enemy_ptr->inflict_effects();
    ASSERT_TRUE(enemy_ptr->effects().empty());
}

TEST_F(EffectTest, vanish_and_neutralize){
    enemy_ptr->add_effect(factory->create("slow", enemy_ptr));
    enemy_ptr->add_effect(factory->create("slow", enemy_ptr));

    enemy_ptr->inflict_effects();

    ASSERT_NE(enemy_ptr->speed(), speed);

    enemy_ptr->vanish_effects();

    ASSERT_EQ(enemy_ptr->speed(), speed);
}

TEST_F(EffectTest, magic_add_remove){
    Magic wizard(*factory);
    wizard.add_magic_effect("slow", 1, 2);

    ASSERT_THROW(wizard.add_magic_effect("slow", 7, 8), std::runtime_error);
    ASSERT_TRUE(wizard.magic_effects().contains("slow"));
    ASSERT_EQ(wizard.magic_effects().size(), 1);

    wizard.remove_magic_effect("slow");

    ASSERT_THROW(wizard.remove_magic_effect("slow"), std::runtime_error);
    ASSERT_FALSE(wizard.magic_effects().contains("slow"));
    ASSERT_TRUE(wizard.magic_effects().empty());
}

TEST_F(EffectTest,  magic_cast_spell){
    Magic wizard(*factory);
    wizard.add_magic_effect("slow", 1, 2);
    wizard.add_magic_effect("poison", 1, 1);

    wizard.cast_spell(enemy_ptr);
    
    ASSERT_EQ(enemy_ptr->effects().size(), 2);

    enemy_ptr->inflict_effects();
    enemy_ptr->inflict_effects();

    ASSERT_NE(enemy_ptr->hp(), max_hp);
    ASSERT_NE(enemy_ptr->speed(), speed);

    enemy_ptr->vanish_effects();

    ASSERT_EQ(enemy_ptr->speed(), speed);
    ASSERT_TRUE(enemy_ptr->effects().empty());
}