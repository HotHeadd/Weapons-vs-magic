#pragma once

#include "i_enemy.hpp"
#include "i_sys_manager.hpp"
#include <memory>

namespace WVM
{

class Enemy: public IEnemy{
public:
    Enemy(ISystemManager& manager,
            hp_t max_hp, 
            double speed, 
            hp_t damage, 
            unsigned gold, 
            Coordinates position);
    void on_death() override;
    void take_damage(hp_t amount) override;
    void update() override;

    void set_speed(double new_speed);

    double speed();
    unsigned damage();
    unsigned gold();

    Enemy& operator= (const Enemy& other) = default;

    std::string_view type() override;
    Enemy& set_type(std::string_view new_type) override;

    std::mutex& mutex() override;
protected:
    virtual void move_to_castle();
    unsigned gold_;
    double speed_;
    hp_t damage_;
    ISystemManager& manager_;

    std::string type_ = "";

    double current_movement_points_ = 0;
    static constexpr double required_movement_points_ = 1000;

    std::mutex enemy_mutex_;
};

} // namespace WVM
