#pragma once

#include <gtest/gtest.h>
#include "layout.hpp"
#include <random>

using namespace WVM;
using MyRNG = std::mt19937;

class LayoutTest : public testing::Test {
public:
    Layout layout;
    void SetUp() override{
        layout = Layout(5, 5);
        layout.at(1, 0).set_type(TileType::WALL);
        layout.at(1, 2).set_type(TileType::WALL);
        layout.at(1, 3).set_type(TileType::WALL);
        layout.at(3, 3).set_type(TileType::WALL);
        layout.at(1, 1).set_type(TileType::FIELD);
        layout.at(3, 1).set_type(TileType::CASTLE);
        layout.at(3, 2).set_type(TileType::CASTLE);
    }
};