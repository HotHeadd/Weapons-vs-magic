#include <gmock/gmock.h>
#include "i_sys_manager.hpp"
#include <memory>
#include "enemy.hpp"
#include "effect_factory.hpp"

#include "effect_factory.hpp"
#include "poisoning.hpp"
#include "weakening.hpp"
#include "slowdown.hpp"

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

class EnemyTest : public testing::Test {
public:
    std::shared_ptr<Enemy> enemy_ptr;
    hp_t max_hp = 100;
    double speed = 10;
    hp_t damage = 10;
    unsigned gold = 10;
    Coordinates position = {7, 8};
    MockManager manager;
    void SetUp() override{
        enemy_ptr = std::make_shared<Enemy>(manager, max_hp, speed, damage, gold, position);
    } 
};

inline std::shared_ptr<Effect> create_poisoning(std::shared_ptr<Effected> target){
    unsigned strength = 1;
    unsigned duration = 1;
    return std::make_shared<Poisoning>(target, strength, duration);
}

inline std::shared_ptr<Effect> create_weakening(std::shared_ptr<Effected> target){
    unsigned strength = 3;
    unsigned ticks = 15;
    return std::make_shared<Weakening>(target, strength, ticks);
}

inline std::shared_ptr<Effect> create_slowdown(std::shared_ptr<Effected> target){
    unsigned strength = 3;
    unsigned ticks = 15;
    return std::make_shared<Slowdown>(target, strength, ticks);
}

class EffectTest : public EnemyTest{
public:
    std::shared_ptr<EffectFactory> factory;
    void SetUp() override{
        enemy_ptr = std::make_shared<Enemy>(manager, max_hp, speed, damage, gold, position);
        factory = std::make_shared<EffectFactory>();
        factory->add_effect("poison", create_poisoning);
        factory->add_effect("slow", create_slowdown);
        factory->add_effect("weak", create_weakening);
    } 
};