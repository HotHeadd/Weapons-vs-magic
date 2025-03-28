#include "healing_enemy.hpp"

namespace WVM
{

HealingEnemy::HealingEnemy(
        ISystemManager& manager,
        hp_t max_hp, 
        double speed, 
        hp_t damage, 
        unsigned gold, 
        Coordinates position,
        double vision,
        double healing_frequency,
        hp_t healing_amount) 
            : Enemy(manager, max_hp, speed, damage, gold, position), 
              healing_amount_(healing_amount), healing_frequency_(healing_frequency), vision_(vision) {}

void HealingEnemy::update(){
    heal();
    move_to_castle();
}

void HealingEnemy::heal(){
    curr_heal_cooldown_ +=  healing_frequency_;
    if (curr_heal_cooldown_ >= required_healing_points_){
        std::vector<std::shared_ptr<IEnemy>> targets;
        provide_targets(targets);
        for (auto& target : targets){
            affect_target(target);
        }
        if (targets.empty()){
            curr_heal_cooldown_ += required_healing_points_ - healing_frequency_;
        }
        curr_heal_cooldown_ -= required_healing_points_;
    }
}

void HealingEnemy::provide_targets(std::vector<std::shared_ptr<IEnemy>>& targets){
    std::unordered_set<std::shared_ptr<IEnemy>>& enemies = manager_.get_enemies();
    for (auto& enemy : enemies){
        if (distance(*enemy, *this) <= vision_){
            targets.push_back(enemy);
        }
    }
}

void HealingEnemy::affect_target(std::shared_ptr<IEnemy>& target){
    target->restore_hp(healing_amount_);
}

} // namespace WVM
