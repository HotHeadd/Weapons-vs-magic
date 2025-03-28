#pragma once

#include "enemy.hpp"
#include "shooting.hpp"
#include "i_sys_manager.hpp"
#include "i_tower.hpp"

namespace WVM
{

class ShootingEnemy : public Enemy, public Shooting{
public:
    ShootingEnemy(
        ISystemManager& manager,
        hp_t max_hp, 
        double speed, 
        hp_t damage,
        unsigned gold, 
        Coordinates position,
        double vision,
        double rapidity,
        hp_t shot_damage
    );

    void update() override;

    double vision_radius() override;
    hp_t shot_damage() override;
    ShootingEnemy& set_vision(double new_vision) override;
    ShootingEnemy& set_shot_damage(hp_t new_damage) override;
protected:
    double rapidity_;
    hp_t shot_damage_;
    double vision_;

    double current_shot_cooldown_ = 0;
    static constexpr double required_shot_points_ = 1000;

    virtual void provide_targets(std::vector<std::shared_ptr<ITower>>& targets);
    virtual void affect_target(std::shared_ptr<ITower> target);
    virtual void shoot();
};

} // namespace WVM
