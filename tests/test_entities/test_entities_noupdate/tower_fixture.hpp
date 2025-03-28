#include <gmock/gmock.h>
#include "i_sys_manager.hpp"
#include <memory>
#include "tower.hpp"
#include "../mocks_and_fixtures.hpp"

#include "magic_tower.hpp"

class TowerTest : public EffectTest {
public:
    std::shared_ptr<Tower> tower_ptr;
    std::vector<std::unordered_map<std::string, std::string>> levelup_rules;
    std::unordered_map<std::string, std::string> first_levelup;
    std::unordered_map<std::string, std::string> second_levelup;
    hp_t max_hp = 100;
    Coordinates pos = {1, 1};
    unsigned cost = 10;
    double vision = 1.5;
    hp_t damage = 10;
    double rapidity = 5;
    void SetUp() override{
        first_levelup["levelup_cost"] = "155";
        first_levelup["damage_up"] = "5";
        first_levelup["vision_up"] = "0.5";
        first_levelup["cost_up"] = "200";
        first_levelup["rapidity_up"] = "3";
        first_levelup["max_hp_up"] = "100";
        first_levelup["add_magic_effect"] = "weak 1 5";
        first_levelup["up_effect_strength"] = "poison 2";

        second_levelup["levelup_cost"] = "300";
        second_levelup["damage_up"] = "500";
        second_levelup["cost_up"] = "1000";
        second_levelup["up_effect_duration"] = "weak 3";

        levelup_rules.push_back(first_levelup);
        levelup_rules.push_back(second_levelup);
        MockManager manager;
        tower_ptr = std::make_shared<Tower>(manager, 
                max_hp,
                pos,
                cost,
                vision,
                damage,
                rapidity,
                levelup_rules);
    }
};

class MagicTowerTest : public TowerTest{
public:
    std::shared_ptr<MagicTower> magic_tower_ptr;
    void SetUp() override {
        TowerTest::SetUp();
        MockManager manager;
        std::unordered_map<std::string, MagicNode> effects;
        effects.emplace("poison", MagicNode{1, 1});
        magic_tower_ptr = std::make_shared<MagicTower>(
            manager,
            *factory, 
            max_hp,
            pos,
            cost,
            vision,
            damage,
            rapidity,
            levelup_rules,
            effects
        );
    }
};