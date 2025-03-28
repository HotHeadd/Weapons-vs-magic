#include "enemy.hpp"
#include "i_system.hpp"

namespace WVM
{

Enemy::Enemy(ISystemManager& manager,
            hp_t max_hp, 
            double speed, 
            hp_t damage, 
            unsigned gold, 
            Coordinates position)
            : manager_(manager) , speed_(speed), damage_(damage), gold_(gold)
{
    max_hp_ = max_hp;
    hp_ = max_hp_;
    position_ = position;
}

void Enemy::update(){
    move_to_castle();
}

void Enemy::move_to_castle(){
    current_movement_points_ += speed_;
    if (current_movement_points_ >= required_movement_points_){
        Layout& layout = manager_.get_layout();
        Coordinates dir = layout(position_).direction();
        move(position()+dir);
        current_movement_points_ -= required_movement_points_;
    }
}

void Enemy::take_damage(hp_t amount){
    hp_ -= amount*damage_multiplier_;
}

void Enemy::on_death(){
    manager_.get_castle().increase_gold(gold_);
}

void Enemy::set_speed(double new_speed){
    speed_ = new_speed;
}

double Enemy::speed(){
    return speed_;
}

unsigned Enemy::damage(){
    return damage_;
}

unsigned Enemy::gold(){
    return gold_;
}

std::string_view Enemy::type() {
    return type_;
}
    
Enemy& Enemy::set_type(std::string_view new_type){
    type_ = new_type;
    return *this;
}


std::mutex& Enemy::mutex(){
    return enemy_mutex_;
}

} // namespace WVM
