#include "trap.hpp"

namespace WVM
{

Trap::Trap(
    ISystemManager& manager,
    Coordinates position,
    unsigned cost,
    double vision_radius,
    double effect_radius,
    hp_t damage) 
            : manager_(manager), cost_(cost), vision_radius_(vision_radius), 
              effect_radius_(effect_radius), damage_(damage){
    position_ = position;
}

void Trap::update(){
    std::vector<std::shared_ptr<Entity>> targets;
    provide_targets(targets);
    if (!targets.empty()){
        for (auto& target : targets){
            affect_target(target);
        }
        is_dead_ = true;
    }
}

void Trap::provide_targets(std::vector<std::shared_ptr<Entity>>& targets) {
    std::unordered_set<std::shared_ptr<IEnemy>>& enemies = manager_.get_enemies();
    bool is_enemy_in_vision=false;
    for (auto& enemy : enemies){
        if (distance(*enemy, *this) <= vision_radius_){
            is_enemy_in_vision=true;
            break;
        }
    }
    if (is_enemy_in_vision){
        for (auto& enemy : enemies){
            if (distance(*enemy, *this) <= effect_radius_){
                targets.push_back(enemy);
            }
        }
    }
}

void Trap::affect_target(std::shared_ptr<Entity> target){
    std::shared_ptr<IEnemy> e_target = std::static_pointer_cast<IEnemy>(target);
    std::lock_guard<std::mutex> lock_enemy(e_target->mutex());
    e_target->take_damage(damage_);
}

void Trap::sell(){
    unsigned sell_cost = cost_/2;
    manager_.get_castle().increase_gold(sell_cost);
    is_dead_ = true;
}

hp_t Trap::shot_damage() {
    return damage_;
}

double Trap::vision_radius() {
    return vision_radius_;
}

unsigned Trap::cost() {
    return cost_;
}

Trap& Trap::set_vision(double new_vision) {
    vision_radius_ = new_vision;
    return *this;
}

Trap& Trap::set_shot_damage(hp_t new_damage) {
    damage_ = new_damage;
    return *this;
}

void Trap::reset_cooldown() {}

void Trap::on_death() {}

bool Trap::is_dead(){
    return is_dead_;
}

std::string_view Trap::type(){
    return type_;
}

Trap& Trap::set_type(std::string_view new_type){
    type_ = new_type;
    return *this;
}

} // namespace WVM
