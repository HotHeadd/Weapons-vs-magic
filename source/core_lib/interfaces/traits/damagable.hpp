#pragma once

#include <algorithm>

namespace WVM
{

using hp_t = double;

class Damagable{
public:
    virtual ~Damagable() = default;
    virtual void take_damage(hp_t amount) = 0;
    virtual void restore_hp(hp_t amount) {hp_ = std::min(hp_ + amount*healing_multiplier_, max_hp_);}

    hp_t hp() {return hp_;};
    hp_t max_hp() {return max_hp_;};
    void set_max_hp(hp_t new_max_hp) {
        max_hp_ = new_max_hp;
        hp_ = std::min(max_hp_, hp_);
    };

    double damage_multiplier() {return damage_multiplier_;}
    void set_damage_multiplier(double new_multiplier) {damage_multiplier_ = new_multiplier;}

    double healing_multiplier() {return healing_multiplier_;}
    void set_healing_multiplier(double new_multiplier) {healing_multiplier_ = new_multiplier;}
protected:
    hp_t max_hp_;
    hp_t hp_;
    double damage_multiplier_=1;
    double healing_multiplier_=1;
};

} // namespace WVM
