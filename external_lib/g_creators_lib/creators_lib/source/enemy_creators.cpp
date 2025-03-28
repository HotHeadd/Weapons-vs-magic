#include "enemy_creators.hpp"
#include "i_factory_manager.hpp"
#include "g_enemy.hpp"

std::shared_ptr<Entity> create_bob(ISystemManager& manager, IFactoryManager& f_manager){
    hp_t bob_hp = 100;
    double bob_speed = 250;
    hp_t bob_damage = 10;
    unsigned bob_gold = 100;
    Coordinates bob_position = {1, 1};
    std::shared_ptr<Enemy> bob = std::make_shared<GEnemy>(manager,
                                                         bob_hp,
                                                         bob_speed,
                                                         bob_damage,
                                                         bob_gold,
                                                         bob_position,
                                                         "assets/textures/entities/bob.jpg");
    return std::static_pointer_cast<Entity>(bob);
}

std::shared_ptr<Entity> create_tank(ISystemManager& manager, IFactoryManager& f_manager){
    hp_t tank_hp = 300;
    double tank_speed = 45;
    hp_t tank_damage = 30;
    unsigned tank_gold = 300;
    Coordinates tank_position = {1, 1};
    std::shared_ptr<Enemy> tank = std::make_shared<GEnemy>(manager,
                                                         tank_hp,
                                                         tank_speed,
                                                         tank_damage,
                                                         tank_gold,
                                                         tank_position,
                                                         "assets/textures/entities/tank.png");
    return std::static_pointer_cast<Entity>(tank);
}

