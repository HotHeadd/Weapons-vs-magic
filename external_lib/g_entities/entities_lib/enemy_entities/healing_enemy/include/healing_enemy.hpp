#pragma once

#include "enemy.hpp"
#include "i_sys_manager.hpp"

namespace WVM
{

class HealingEnemy : public Enemy {
public:
    HealingEnemy(
        ISystemManager& manager,
        hp_t max_hp, 
        double speed, 
        hp_t damage, 
        unsigned gold, 
        Coordinates position,
        double vision,
        double healing_frequency,
        hp_t healing_amount
    );
    void update() override;
    
protected:
    virtual void provide_targets(std::vector<std::shared_ptr<IEnemy>>& targets);
    virtual void affect_target(std::shared_ptr<IEnemy>& target);

    double vision_;
    hp_t healing_amount_;
    double healing_frequency_;

    double curr_heal_cooldown_ = 0;
    static constexpr double required_healing_points_ = 1000;

    virtual void heal();
};

} // namespace WVM
