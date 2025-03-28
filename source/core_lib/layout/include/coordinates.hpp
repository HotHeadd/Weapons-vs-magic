#pragma once

#include <cstddef>
#include <compare>
#include <cmath>

namespace WVM
{

struct Coordinates{
    int x;
    int y;
    std::strong_ordering operator<=> (const Coordinates& other) const{
        if (std::pow(x, 2)+std::pow(y, 2) > std::pow(other.x, 2) + std::pow(other.y, 2)) {
            return std::strong_ordering::greater;
        }
        if (std::pow(x, 2)+std::pow(y, 2) < std::pow(other.x, 2) + std::pow(other.y, 2)){
            return std::strong_ordering::less;
        }
        return std::strong_ordering::equal;
    }
    bool operator== (const Coordinates& other) const{
        return ((*this) <=> other) == 0;
    }

    Coordinates operator+ (const Coordinates& other) const{
        return {x+other.x, y+other.y};
    }
};

} // namespace WVM