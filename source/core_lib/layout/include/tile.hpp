#pragma once

#include <utility>
#include <limits>
#include "coordinates.hpp"

namespace WVM{
enum class TileType{
    ROAD,
    FIELD,
    WALL,
    CASTLE,
    UNDEFINED,
};

class Tile{
public:
    static constexpr unsigned UND_DIST = -1u;

    static constexpr Coordinates UND_DIRECTION = {std::numeric_limits<short>::min(), std::numeric_limits<short>::min()};
    static constexpr Coordinates UP = {-1, 0};
    static constexpr Coordinates DOWN = {1, 0};
    static constexpr Coordinates LEFT = {0, -1};
    static constexpr Coordinates RIGHT = {0, 1};
    static constexpr Coordinates U_LEFT = {-1, -1};
    static constexpr Coordinates U_RIGHT = {-1, 1};
    static constexpr Coordinates D_LEFT = {1, -1};
    static constexpr Coordinates D_RIGHT = {1, 1};

    Tile() : type_(TileType::ROAD), direction_(UND_DIRECTION), steps_to_castle_(UND_DIST) {}
    Tile(TileType type) : type_(type), direction_(UND_DIRECTION), steps_to_castle_(UND_DIST) {}

    void set_type(TileType type) {type_ = type;};
    void set_direction(Coordinates way) {direction_ = way;};
    void set_steps(unsigned amount) {steps_to_castle_ = amount;}

    TileType type() const {return type_;};
    Coordinates direction() const {return direction_;};
    unsigned steps_to_castle() const {return steps_to_castle_;};
private:
    TileType type_;
    Coordinates direction_;
    unsigned steps_to_castle_;
};
}
