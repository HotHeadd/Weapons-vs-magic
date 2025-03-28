#include <gtest/gtest.h>
#include "tower.hpp"
#include "tower_fixture.hpp"


TEST(tower, constructor_getters){
    std::vector<std::unordered_map<std::string, std::string>> levelup_rules;
    std::unordered_map<std::string, std::string> new_rule;
    new_rule["levelup_cost"] = "155";
    levelup_rules.push_back(new_rule);
    MockManager manager;
    hp_t max_hp = 100;
    Coordinates pos(1, 1);
    unsigned cost = 10;
    double vision = 1.5;
    hp_t damage = 10;
    double rapidity = 5;

    Tower tower(manager, 
                max_hp,
                pos,
                cost,
                vision,
                damage,
                rapidity,
                levelup_rules);

    ASSERT_EQ(tower.max_hp(), max_hp);
    ASSERT_EQ(tower.hp(), max_hp);
    ASSERT_EQ(tower.position(), pos);
    ASSERT_EQ(tower.cost(), cost);
    ASSERT_EQ(tower.vision_radius(), vision);
    ASSERT_EQ(tower.shot_damage(), damage);
    ASSERT_EQ(tower.rapidity(), rapidity);
    ASSERT_EQ(tower.max_level(), 2);
    ASSERT_EQ(tower.level(), 1);
    ASSERT_EQ(tower.levelup_cost(), 155);
}

TEST_F(TowerTest, setters){
    hp_t new_damage = 100500;
    double new_rapidity = 100;
    double new_vision = 50;
    Strategy new_strategy = Strategy::HEALTHIEST;
    tower_ptr->set_shot_damage(new_damage);
    tower_ptr->set_rapidity(new_rapidity);
    tower_ptr->set_vision(new_vision);
    tower_ptr->set_strategy(new_strategy);

    ASSERT_EQ(tower_ptr->shot_damage(), new_damage);
    ASSERT_EQ(tower_ptr->rapidity(), new_rapidity);
    ASSERT_EQ(tower_ptr->vision_radius(), new_vision);
    ASSERT_EQ(tower_ptr->strategy(), new_strategy);
}

TEST_F(TowerTest, level_up){
    ASSERT_EQ(tower_ptr->levelup_cost().value(), std::stoi(first_levelup["levelup_cost"]));

    std::unordered_map<std::string, std::string>* instr = tower_ptr->next_level_ups();

    ASSERT_EQ(instr->at("damage_up"), first_levelup["damage_up"]);
    ASSERT_EQ(instr->at("vision_up"), first_levelup["vision_up"]);
    ASSERT_EQ(instr->at("cost_up"), first_levelup["cost_up"]);
    ASSERT_EQ(instr->at("rapidity_up"), first_levelup["rapidity_up"]);
    ASSERT_EQ(instr->at("max_hp_up"), first_levelup["max_hp_up"]);

    tower_ptr->level_up();
    
    ASSERT_EQ(tower_ptr->level(), 2);
    ASSERT_EQ(tower_ptr->max_hp(), max_hp+std::stoi(first_levelup["max_hp_up"]));
    ASSERT_EQ(tower_ptr->hp(), max_hp+std::stoi(first_levelup["max_hp_up"]));
    ASSERT_EQ(tower_ptr->shot_damage(), damage+std::stoi(first_levelup["damage_up"]));
    ASSERT_EQ(tower_ptr->vision_radius(), vision+std::stoi(first_levelup["vision_up"]));
    ASSERT_EQ(tower_ptr->cost(), cost+std::stoi(first_levelup["cost_up"]));
    ASSERT_EQ(tower_ptr->rapidity(), rapidity+std::stoi(first_levelup["rapidity_up"]));

    instr = tower_ptr->next_level_ups();

    ASSERT_EQ(tower_ptr->levelup_cost().value(), std::stoi(second_levelup["levelup_cost"]));
    ASSERT_EQ(instr->at("damage_up"), second_levelup["damage_up"]);
    ASSERT_EQ(instr->at("cost_up"), second_levelup["cost_up"]);
    ASSERT_THROW(instr->at("vision_up"), std::out_of_range);
    ASSERT_THROW(instr->at("max_hp_up"), std::out_of_range);
    ASSERT_THROW(instr->at("rapidity_up"), std::out_of_range);

    tower_ptr->level_up();

    ASSERT_EQ(tower_ptr->level(), 3);
    ASSERT_EQ(tower_ptr->max_hp(), max_hp+std::stoi(first_levelup["max_hp_up"]));
    ASSERT_EQ(tower_ptr->hp(), max_hp+std::stoi(first_levelup["max_hp_up"]));
    ASSERT_EQ(tower_ptr->shot_damage(), damage+std::stoi(first_levelup["damage_up"]) + std::stoi(second_levelup["damage_up"]));
    ASSERT_EQ(tower_ptr->vision_radius(), vision+std::stoi(first_levelup["vision_up"]));
    ASSERT_EQ(tower_ptr->cost(), cost+std::stoi(first_levelup["cost_up"]) + std::stoi(second_levelup["cost_up"]));
    ASSERT_EQ(tower_ptr->rapidity(), rapidity+std::stoi(first_levelup["rapidity_up"]));

    instr = tower_ptr->next_level_ups();
    ASSERT_FALSE(tower_ptr->levelup_cost().has_value());
    ASSERT_EQ(instr, nullptr);
}

TEST_F(MagicTowerTest, level_up){
    std::unordered_map<std::string, MagicNode>& effects = magic_tower_ptr->magic_effects();
    ASSERT_EQ(effects.size(), 1);

    magic_tower_ptr->level_up();

    ASSERT_EQ(magic_tower_ptr->level(), 2);
    ASSERT_EQ(magic_tower_ptr->max_hp(), max_hp+std::stoi(first_levelup["max_hp_up"]));
    ASSERT_EQ(magic_tower_ptr->hp(), max_hp+std::stoi(first_levelup["max_hp_up"]));
    ASSERT_EQ(magic_tower_ptr->shot_damage(), damage+std::stoi(first_levelup["damage_up"]));
    ASSERT_EQ(magic_tower_ptr->vision_radius(), vision+std::stoi(first_levelup["vision_up"]));
    ASSERT_EQ(magic_tower_ptr->cost(), cost+std::stoi(first_levelup["cost_up"]));
    ASSERT_EQ(magic_tower_ptr->rapidity(), rapidity+std::stoi(first_levelup["rapidity_up"]));

    effects = magic_tower_ptr->magic_effects();

    ASSERT_EQ(effects.size(), 2);
    ASSERT_TRUE(effects.contains("weak"));
    ASSERT_TRUE(effects.contains("poison"));
    ASSERT_EQ(effects["poison"].e_strength, 3);
    ASSERT_EQ(effects["poison"].e_duration, 1);
    ASSERT_EQ(effects["weak"].e_strength, 1);
    ASSERT_EQ(effects["weak"].e_duration, 5);

    magic_tower_ptr->level_up();
    ASSERT_EQ(magic_tower_ptr->max_hp(), max_hp+std::stoi(first_levelup["max_hp_up"]));
    ASSERT_EQ(magic_tower_ptr->hp(), max_hp+std::stoi(first_levelup["max_hp_up"]));
    ASSERT_EQ(magic_tower_ptr->shot_damage(), damage+std::stoi(first_levelup["damage_up"]) + std::stoi(second_levelup["damage_up"]));
    ASSERT_EQ(magic_tower_ptr->vision_radius(), vision+std::stoi(first_levelup["vision_up"]));
    ASSERT_EQ(magic_tower_ptr->cost(), cost+std::stoi(first_levelup["cost_up"]) + std::stoi(second_levelup["cost_up"]));
    ASSERT_EQ(magic_tower_ptr->rapidity(), rapidity+std::stoi(first_levelup["rapidity_up"]));

    effects = magic_tower_ptr->magic_effects();

    ASSERT_EQ(effects.size(), 2);
    ASSERT_TRUE(effects.contains("weak"));
    ASSERT_TRUE(effects.contains("poison"));
    ASSERT_EQ(effects["poison"].e_strength, 3);
    ASSERT_EQ(effects["poison"].e_duration, 1);
    ASSERT_EQ(effects["weak"].e_strength, 1);
    ASSERT_EQ(effects["weak"].e_duration, 8);
}