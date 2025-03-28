#pragma once

#include "coordinates.hpp"
#include "object.hpp"

namespace WVM
{

class Entity : public Object{
public:
    virtual ~Entity() = default;
    Coordinates& position() {return position_;};
    virtual void move(Coordinates new_position) {
        position_ = new_position;
    };
    virtual void update() = 0;
protected:
    friend double distance(Entity& lhs, Entity& rhs);
    Coordinates position_;
};

inline double distance(Entity& lhs, Entity& rhs){
    Coordinates& r_pos = rhs.position();
    Coordinates& l_pos = lhs.position();
    return sqrt(pow(r_pos.x-l_pos.x, 2) + pow(abs(r_pos.y-l_pos.y), 2));
}

} // namespace WVM
