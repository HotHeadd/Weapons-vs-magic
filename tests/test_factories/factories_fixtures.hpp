#pragma once

#include <gmock/gmock.h>
#include "i_sys_manager.hpp"
#include "i_factory_manager.hpp"
#include "i_effect_factory.hpp"
#include "i_enemy_factory.hpp"
#include "i_tower_factory.hpp"
#include "i_trap_factory.hpp"

using namespace WVM;

class MockManager : public ISystemManager{
public:
    MOCK_METHOD(ISystem&, get_system, (SystemTag tag), (override));
    MOCK_METHOD(Layout&, get_layout, (), (override));

    MOCK_METHOD(std::unordered_set<std::shared_ptr<IDefence>>&, get_defence, (), (override));
    MOCK_METHOD(std::unordered_set<std::shared_ptr<IEnemy>>&, get_enemies, (), (override));
    MOCK_METHOD(Castle&, get_castle, (), (override));

    MOCK_METHOD(ManagerIterator, begin, (), (override));
    MOCK_METHOD(ManagerIterator, end, (), (override));
};

class MockFactoryManager : public IFactoryManager{
    MOCK_METHOD(IEnemyFactory&, get_enemy_factory, (), (override));
    MOCK_METHOD(ITowerFactory&, get_tower_factory, (), (override));
    MOCK_METHOD(ITrapFactory&, get_trap_factory, (), (override));
    MOCK_METHOD(IEffectFactory&, get_effect_factory, (), (override));
};