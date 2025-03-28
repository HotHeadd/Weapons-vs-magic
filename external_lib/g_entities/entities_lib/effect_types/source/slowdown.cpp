#include "slowdown.hpp"
#include <cmath>

namespace WVM
{

Slowdown::Slowdown(std::shared_ptr<Effected> target) 
        : strength_(1), turns_to_last_(1) {
    std::shared_ptr<IEnemy> checked_target = std::dynamic_pointer_cast<IEnemy>(target);
    if (!checked_target){
        throw std::logic_error("Slowdown can't be applied to this target (not enemy)");
    }
    target_ = checked_target;
}

Slowdown::Slowdown(std::shared_ptr<Effected> target, unsigned strength, unsigned turns_to_last) 
        : strength_(strength), turns_to_last_(turns_to_last) {
    std::shared_ptr<IEnemy> checked_target = std::dynamic_pointer_cast<IEnemy>(target);
    if (!checked_target){
        throw std::logic_error("Slowdown can't be applied to this target (not enemy)");
    }
    target_ = checked_target;
}

void Slowdown::inflict(){
    if (turns_to_last_ != 0){
    if (auto shared_target = target_.lock()){
        if (!is_inflicted_){
            shared_target->set_speed(
                        shared_target->speed()*std::exp(-static_cast<double>(strength_)*slow_coef));
            is_inflicted_ = true;
        }
    }
    turns_to_last_ -= 1;
    }
}

void Slowdown::neutralize() {
    if (auto shared_target = target_.lock()){
    if (is_inflicted_){
        shared_target->set_speed(
                        shared_target->speed()/std::exp(-static_cast<double>(strength_)*slow_coef));
        is_inflicted_ = false;
    }
    }
}

unsigned Slowdown::turns_to_last() const {
    return turns_to_last_;
}

unsigned Slowdown::strength() const{
    return strength_;
}

void Slowdown::set_strength(unsigned new_strength){
    strength_ = new_strength;
}

void Slowdown::set_duration(unsigned new_duration){
    turns_to_last_ = new_duration;
}

std::string_view Slowdown::type(){
    return type_;
}
Slowdown& Slowdown::set_type(std::string_view new_type){
    type_ = new_type;
    return *this;
}

void Slowdown::on_death() {}


} // namespace WVM
