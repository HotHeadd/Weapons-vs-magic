#include "weakening.hpp"
#include "damagable.hpp"

namespace WVM
{

Weakening::Weakening(std::shared_ptr<Effected> target) 
        : strength_(1), turns_to_last_(1) {
    std::shared_ptr<Damagable> checked_target = std::dynamic_pointer_cast<Damagable>(target);
    if (!checked_target){
        throw std::logic_error("Poisoning can't be applied to undamagable target");
    }
    target_ = checked_target;
}

Weakening::Weakening(std::shared_ptr<Effected> target, unsigned strength, unsigned turns_to_last) 
        : strength_(strength), turns_to_last_(turns_to_last) {
    std::shared_ptr<Damagable> checked_target = std::dynamic_pointer_cast<Damagable>(target);
    if (!checked_target){
        throw std::logic_error("Poisoning can't be applied to undamagable target");
    }
    target_ = checked_target;
}

void Weakening::inflict(){
    if (turns_to_last_ != 0){
    if (auto shared_target = target_.lock()){
        if (!is_inflicted_){
            shared_target->set_damage_multiplier(
                        shared_target->damage_multiplier()+strength_*multiplier_addition);
            is_inflicted_ = true;
        }
    }
    turns_to_last_ -= 1;
    }
}

void Weakening::neutralize() {
    if (auto shared_target = target_.lock()){
    if (is_inflicted_){
        shared_target->set_damage_multiplier(
                        shared_target->damage_multiplier()-strength_*multiplier_addition);
        is_inflicted_ = false;
    }
    }
}

unsigned Weakening::turns_to_last() const {
    return turns_to_last_;
}

unsigned Weakening::strength() const{
    return strength_;
}

void Weakening::set_strength(unsigned new_strength){
    strength_ = new_strength;
}

void Weakening::set_duration(unsigned new_duration){
    turns_to_last_ = new_duration;
}

std::string_view Weakening::type(){
    return type_;
}
Weakening& Weakening::set_type(std::string_view new_type){
    type_ = new_type;
    return *this;
}

void Weakening::on_death() {}

} // namespace WVM
