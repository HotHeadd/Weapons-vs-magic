#include "poisoning.hpp"
#include "damagable.hpp"

namespace WVM
{

Poisoning::Poisoning(std::shared_ptr<Effected> target) 
        : strength_(1), ticks_(1), current_cooldown_(0){
    std::shared_ptr<Damagable> checked_target = std::dynamic_pointer_cast<Damagable>(target);
    if (!checked_target){
        throw std::logic_error("Poisoning can't be applied to undamagable target");
    }
    target_ = checked_target;
}

Poisoning::Poisoning(std::shared_ptr<Effected> target, unsigned strength, unsigned turns_to_last)
        : strength_(strength){
    std::shared_ptr<Damagable> checked_target = std::dynamic_pointer_cast<Damagable>(target);
    if (!checked_target){
        throw std::logic_error("Poisoning can't be applied to undamagable target");
    }
    target_ = checked_target;
    set_duration(turns_to_last);
}

void Poisoning::inflict(){
    if (ticks_ != 0){
        if (!current_cooldown_){
            if (auto shared_target = target_.lock()){
                shared_target->take_damage(hp_per_tick*strength_);
                ticks_ -= 1;
                current_cooldown_ = tick_cooldown;
            }
        }
    current_cooldown_ -= 1;
    }
}

void Poisoning::neutralize() {} // ничего не делает

unsigned Poisoning::turns_to_last() const { // +1 за тот ход в который произойдет последний тик
    if ((ticks_*tick_cooldown + 1) >= (tick_cooldown - current_cooldown_)){
        return ticks_*tick_cooldown + 1-(tick_cooldown - current_cooldown_);
    }
    return 0;
}

unsigned Poisoning::strength() const{
    return strength_;
}

void Poisoning::set_strength(unsigned new_strength){
    strength_ = new_strength;
}

void Poisoning::set_duration(unsigned new_duration){
    ticks_ = (new_duration-1)/tick_cooldown + 1;
    current_cooldown_ = (new_duration-1)%tick_cooldown;
}

std::string_view Poisoning::type(){
    return type_;
}
Poisoning& Poisoning::set_type(std::string_view new_type){
    type_ = new_type;
    return *this;
}

void Poisoning::on_death() {}

} // namespace WVM
