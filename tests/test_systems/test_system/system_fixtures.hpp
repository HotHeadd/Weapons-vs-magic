#pragma once

#include <gmock/gmock.h>
#include "i_enemy.hpp"
#include "i_defence.hpp"
#include "i_lair.hpp"
#include "system_manager.hpp"
#include "effected.hpp"

using namespace WVM;

class MockEnemy : public IEnemy {
public:
    MOCK_METHOD(void, set_speed, (double new_speed), (override));
    MOCK_METHOD(double, speed, (), (override));
    MOCK_METHOD(unsigned, damage, (), (override));
    MOCK_METHOD(unsigned, gold, (), (override));
    MOCK_METHOD(void, take_damage, (hp_t amount), (override));
    MOCK_METHOD(void, update, (), (override));
    MOCK_METHOD(void, on_death, (), (override));
    MOCK_METHOD(void, inflict_effects, (), ());
    MOCK_METHOD(void, vanish_effects, (), ());
    MOCK_METHOD(hp_t, hp, (), ());
    MOCK_METHOD(Coordinates, position, (), ());
    MOCK_METHOD(std::string_view, type, (), (override));
    MOCK_METHOD(IEnemy&, set_type,(std::string_view new_type), (override));
};

class MockDefence : public IDefence{
public:
    MOCK_METHOD(void, sell, (), (override));
    MOCK_METHOD(void, update, (), (override));
    MOCK_METHOD(unsigned, cost, (), (override));
    MOCK_METHOD(void, reset_cooldown, (), (override));
    MOCK_METHOD(void, provide_targets, (std::vector<std::shared_ptr<Entity>>&), (override));
    MOCK_METHOD(void, affect_target, (std::shared_ptr<Entity>), (override));
    MOCK_METHOD(void, on_death, (), (override));
    MOCK_METHOD(bool, is_dead, (), (override));
    MOCK_METHOD(void, inflict_effects, (), ());
    MOCK_METHOD(void, vanish_effects, (), ());
    MOCK_METHOD(void, add_effect, (std::shared_ptr<Effect> effect), ());
    MOCK_METHOD(void, remove_effect,(std::shared_ptr<Effect> effect), ());
    MOCK_METHOD(std::unordered_set<std::shared_ptr<Effect>>&, effects, (), ());
    MOCK_METHOD(std::string_view, type, (), (override));
    MOCK_METHOD(IDefence&, set_type,(std::string_view new_type), (override));
};

class ManagerTest : public testing::Test{
public:
    std::shared_ptr<Layout> layout = std::make_shared<Layout>(5, 5);
    std::shared_ptr<Castle> castle = std::make_shared<Castle>(100);
    std::shared_ptr<SystemManager> manager;
    void SetUp() override{
        manager = std::make_shared<SystemManager>(layout, castle);
    }
};

class MockLair : public ILair{
public:
    MOCK_METHOD(void, on_death,(), (override));
    MOCK_METHOD(json, save, (), (override));
    MOCK_METHOD(void, load, (json&), (override));
    MOCK_METHOD(std::string_view, type, (), (override));
    MOCK_METHOD(IDefence&, set_type,(std::string_view new_type), (override));
    MOCK_METHOD(void, update,(), (override));
    MOCK_METHOD(void, wave_up, (), (override));
    MOCK_METHOD(void, add_spawn_instructions,((std::vector<std::unordered_map<std::string, LairNode>>)), (override));
    MOCK_METHOD((std::vector<std::unordered_map<std::string, LairNode>>&), spawn_instructions,(), (override));
    MOCK_METHOD(bool, no_enemies_left,(), (override));
};