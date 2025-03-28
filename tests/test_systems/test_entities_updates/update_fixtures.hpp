#pragma once 

#include <gtest/gtest.h>
#include "system_manager.hpp"
#include "enemy.hpp"
#include "tower.hpp"
#include "enemy_factory.hpp"
#include "lair.hpp"
#include "factory_manager.hpp"
#include "creators.hpp"

using namespace WVM;

class UpdateTest : public testing::Test{
public:
    hp_t castle_hp = 100;
    std::shared_ptr<Layout> layout = std::make_shared<Layout>(10, 10);
    std::shared_ptr<Castle> castle = std::make_shared<Castle>(castle_hp);
    std::shared_ptr<SystemManager> manager;
    std::shared_ptr<FactoryManager> f_manager;
    std::shared_ptr<Enemy> enemy_ptr;
    std::shared_ptr<Enemy> enemy_ptr_clone;
    std::shared_ptr<Tower> tower_ptr;

    std::shared_ptr<EnemyFactory> enemy_factory;
    std::shared_ptr<Lair> lair_ptr;

    hp_t e_max_hp = 100;
    double e_speed = 10;
    unsigned e_damage = 10;
    unsigned e_gold = 10;
    Coordinates e_position = {7, 8};

    hp_t t_max_hp = 100;
    Coordinates t_pos = {1, 1};
    unsigned t_cost = 10;
    double t_vision = 1.5;
    hp_t t_damage = 10;
    double t_rapidity = 5;
    std::vector<std::unordered_map<std::string, std::string>> t_levelup_rules;
    void SetUp() override {
        setup_layout();
        layout->calculate_paths();
        manager = std::make_shared<SystemManager>(layout, castle);
        f_manager = std::make_shared<FactoryManager>(*manager);
        enemy_ptr = std::make_shared<Enemy>(*manager, e_max_hp, e_speed, e_damage, e_gold, e_position);
        enemy_ptr_clone = std::make_shared<Enemy>(*manager, e_max_hp, e_speed, e_damage, e_gold, e_position);
        tower_ptr  = std::make_shared<Tower>(*manager, 
                t_max_hp,
                t_pos,
                t_cost,
                t_vision,
                t_damage,
                t_rapidity,
                t_levelup_rules);
        manager->get_system(SystemTag::ENEMY).add(enemy_ptr);
        manager->get_system(SystemTag::ENEMY).add(enemy_ptr_clone);
        manager->get_system(SystemTag::DEFENCE).add(tower_ptr);
        tower_ptr->move(Coordinates{1, 2});
        enemy_ptr->move(Coordinates{0, 2});
        enemy_ptr_clone->move(Coordinates{2, 2});

        enemy_factory = std::make_shared<EnemyFactory>(*manager, *f_manager);
        enemy_factory->add_enemy("bob", create_bob);
        enemy_factory->add_enemy("tank", create_tank);
        lair_ptr = std::make_shared<Lair>(*manager, *enemy_factory, Coordinates{0, 0});
    }
protected:
    void setup_layout(){
        layout->operator()(1, 0).set_type(TileType::WALL);
        layout->operator()(1, 1).set_type(TileType::WALL);
        layout->operator()(1, 2).set_type(TileType::FIELD);
        layout->operator()(1, 3).set_type(TileType::WALL);
        layout->operator()(1, 4).set_type(TileType::WALL);
        layout->operator()(1, 5).set_type(TileType::WALL);
        layout->operator()(1, 6).set_type(TileType::WALL);
        layout->operator()(1, 7).set_type(TileType::WALL);
        layout->operator()(1, 8).set_type(TileType::WALL);
        layout->operator()(6, 2).set_type(TileType::WALL);
        layout->operator()(6, 3).set_type(TileType::WALL);
        layout->operator()(6, 4).set_type(TileType::WALL);
        layout->operator()(6, 5).set_type(TileType::WALL);
        layout->operator()(6, 6).set_type(TileType::WALL);
        layout->operator()(6, 7).set_type(TileType::WALL);
        layout->operator()(6, 8).set_type(TileType::WALL);
        layout->operator()(6, 9).set_type(TileType::WALL);
        layout->operator()(7, 2).set_type(TileType::WALL);
        layout->operator()(8, 7).set_type(TileType::WALL);
        layout->operator()(9, 7).set_type(TileType::WALL);

        layout->operator()(8, 0).set_type(TileType::CASTLE);
        layout->operator()(8, 1).set_type(TileType::CASTLE);
        layout->operator()(9, 0).set_type(TileType::CASTLE);
        layout->operator()(9, 1).set_type(TileType::CASTLE);
    }
};