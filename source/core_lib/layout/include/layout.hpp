#pragma once

#include "tile.hpp"
#include "matrix.hpp"
#include "coordinates.hpp"
#include "persistable.hpp"
#include <string>
#include <memory>

namespace WVM{

class Layout : public Matrix<Tile>{
public:
    using Matrix<Tile>::Matrix;
    using Matrix<Tile>::operator();

    void calculate_paths();
    Tile& operator() (const Coordinates& pos);

    bool contains(const Coordinates& pos);

    json save();
    static std::shared_ptr<Layout> load(json&);
private:
};
}
