#pragma once

#include "../traits/damagable.hpp"
#include "../traits/entity.hpp"
#include "effected.hpp"
#include <string_view>
#include <thread>

namespace WVM
{

class IEnemy: public Effected, public Entity, public Damagable{
public:
    virtual void set_speed(double new_speed)=0;

    virtual double speed() = 0;
    virtual unsigned damage() = 0;
    virtual unsigned gold() = 0;

    virtual std::mutex& mutex() = 0;
protected:
};

} // namespace WVM
