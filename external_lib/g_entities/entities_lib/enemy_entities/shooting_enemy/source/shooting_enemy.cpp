#include "shooting_enemy.hpp"
#include <limits>

namespace WVM
{

ShootingEnemy::ShootingEnemy(
        ISystemManager& manager,
        hp_t max_hp, 
        double speed, 
        hp_t damage,
        unsigned gold, 
        Coordinates position,
        double vision,
        double rapidity,
        hp_t shot_damage) : 
            Enemy(manager, max_hp, speed, damage, gold, position), 
            shot_damage_(shot_damage), vision_(vision), rapidity_(rapidity) {}

void ShootingEnemy::update(){
    shoot();
    move_to_castle();
}

void ShootingEnemy::shoot(){
    current_shot_cooldown_ += rapidity_;
    if (current_shot_cooldown_ >=  required_shot_points_){
        std::vector<std::shared_ptr<ITower>> targets;
        provide_targets(targets);
        for (auto& target : targets){
            affect_target(target);
        }
        if (targets.empty()){
            current_shot_cooldown_ +=  required_shot_points_ - rapidity_;
        }
        current_shot_cooldown_ -= required_shot_points_;
    }
}

void ShootingEnemy::provide_targets(std::vector<std::shared_ptr<ITower>>& targets){
    std::unordered_set<std::shared_ptr<IDefence>>& defence = manager_.get_defence();
    double max_dist = std::numeric_limits<double>::max();
    for (auto& target : defence){
        std::shared_ptr<ITower> tower = std::dynamic_pointer_cast<ITower>(target);
        if (tower){
            double c_dist = distance(*tower, *this);
            if (c_dist <= vision_ and c_dist < max_dist){
                max_dist = c_dist;
                targets.push_back(tower);
            }
        }
    }
}

void ShootingEnemy::affect_target(std::shared_ptr<ITower> target){
    target->take_damage(damage_);
}

double ShootingEnemy::vision_radius(){
    return vision_;
}

hp_t ShootingEnemy::shot_damage(){
    return shot_damage_;
}

ShootingEnemy& ShootingEnemy::set_vision(double new_vision){
    vision_ = new_vision;
    return *this;
}

ShootingEnemy& ShootingEnemy::set_shot_damage(hp_t new_damage){
    shot_damage_ = new_damage;
    return *this;
}

} // namespace WVM
