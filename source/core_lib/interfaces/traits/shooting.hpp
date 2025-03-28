#pragma once

#include "damagable.hpp"

namespace WVM
{

class Shooting {
public:
    virtual double vision_radius() = 0;
    virtual hp_t shot_damage() = 0;

    virtual Shooting& set_vision(double new_vision) = 0;
    virtual Shooting& set_shot_damage(hp_t new_damage) = 0;
protected:
};

} // namespace WVM
