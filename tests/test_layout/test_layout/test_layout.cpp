#include <gtest/gtest.h>
#include "layout.hpp"
#include "layout_fixtures.hpp"

using namespace WVM;

TEST(layout, empty_consturctor){
    Tile t(TileType::ROAD);
    Layout layout(5, 5, t);
    for (auto& elem : layout){
        ASSERT_EQ(elem.type(), TileType::ROAD);
    }
    for (int i=0; i<layout.rows(); i++){
        for (int j=0; j<layout.columns(); j++){
            EXPECT_NO_THROW(auto a = layout.at(i, j));
            ASSERT_EQ(layout.at(i, j).type(), TileType::ROAD);
        }
    }
}

TEST_F(LayoutTest, calculate_paths){
    layout.calculate_paths();
    ASSERT_NO_THROW(auto a = layout.at(0, 0));
    for (auto& tile : layout){
       if (tile.type() == TileType::ROAD){
            ASSERT_NE(tile.steps_to_castle(), 0);
            ASSERT_NE(tile.steps_to_castle(), Tile::UND_DIST);
       }
       if (tile.type() == TileType::CASTLE){
            ASSERT_EQ(tile.steps_to_castle(), 0);
       }
    }

    // ASSERT_EQ(layout.at(1, 0).type(), TileType::WALL);
    // ASSERT_EQ(layout.at(1, 0).direction(), Tile::UND_DIRECTION);
    // ASSERT_EQ(layout.at(1, 1).type(), TileType::FIELD);
    // ASSERT_EQ(layout.at(1, 1).direction(), Tile::UND_DIRECTION);
    // ASSERT_EQ(layout.at(1, 1).steps_to_castle(), Tile::UND_DIST);
    // ASSERT_EQ(layout.at(1, 2).type(), TileType::WALL);
    // ASSERT_EQ(layout.at(1, 2).direction(), Tile::UND_DIRECTION);
    // ASSERT_EQ(layout.at(1, 2).steps_to_castle(), Tile::UND_DIST);
    // ASSERT_EQ(layout.at(1, 3).type(), TileType::WALL);
    // ASSERT_EQ(layout.at(1, 3).direction(), Tile::UND_DIRECTION);
    // ASSERT_EQ(layout.at(1, 3).steps_to_castle(), Tile::UND_DIST);
    // ASSERT_EQ(layout.at(3, 3).type(), TileType::WALL);
    // ASSERT_EQ(layout.at(3, 3).direction(), Tile::UND_DIRECTION);
    // ASSERT_EQ(layout.at(3, 3).steps_to_castle(), Tile::UND_DIST);

    // ASSERT_EQ(layout.at(0, 0).direction(), Tile::RIGHT);
    // ASSERT_EQ(layout.at(0, 0).steps_to_castle(), 6);
    // ASSERT_EQ(layout.at(0, 1).direction(), Tile::RIGHT);
    // ASSERT_EQ(layout.at(0, 1).steps_to_castle(), 5);
    // ASSERT_EQ(layout.at(0, 2).direction(), Tile::RIGHT);
    // ASSERT_EQ(layout.at(0, 2).steps_to_castle(), 4);
    // ASSERT_EQ(layout.at(0, 3).direction(), Tile::D_RIGHT);
    // ASSERT_EQ(layout.at(0, 3).steps_to_castle(), 3);
    // ASSERT_EQ(layout.at(0, 4).direction(), Tile::DOWN);
    // ASSERT_EQ(layout.at(0, 4).steps_to_castle(), 3);

    // ASSERT_EQ(layout.at(1, 4).direction(), Tile::D_LEFT);
    // ASSERT_EQ(layout.at(1, 4).steps_to_castle(), 2);

    // ASSERT_EQ(layout.at(2, 0).direction(), Tile::D_RIGHT);
    // ASSERT_EQ(layout.at(2, 0).steps_to_castle(), 1);
    // ASSERT_EQ(layout.at(2, 1).direction(), Tile::DOWN);
    // ASSERT_EQ(layout.at(2, 1).steps_to_castle(), 1);
    // ASSERT_EQ(layout.at(2, 2).direction(), Tile::DOWN);
    // ASSERT_EQ(layout.at(2, 2).steps_to_castle(), 1);
    // ASSERT_EQ(layout.at(2, 3).direction(), Tile::D_LEFT);
    // ASSERT_EQ(layout.at(2, 3).steps_to_castle(), 1);
    // ASSERT_EQ(layout.at(2, 4).direction(), Tile::LEFT);
    // ASSERT_EQ(layout.at(2, 4).steps_to_castle(), 2);

    // ASSERT_EQ(layout.at(3, 0).direction(), Tile::RIGHT);
    // ASSERT_EQ(layout.at(3, 0).steps_to_castle(), 1);
    // ASSERT_EQ(layout.at(3, 4).direction(), Tile::U_LEFT);
    // ASSERT_EQ(layout.at(3, 4).steps_to_castle(), 2);

    // ASSERT_EQ(layout.at(4, 0).direction(), Tile::U_RIGHT);
    // ASSERT_EQ(layout.at(4, 0).steps_to_castle(), 1);
    // ASSERT_EQ(layout.at(4, 1).direction(), Tile::UP);
    // ASSERT_EQ(layout.at(4, 1).steps_to_castle(), 1);
    // ASSERT_EQ(layout.at(4, 2).direction(), Tile::UP);
    // ASSERT_EQ(layout.at(4, 2).steps_to_castle(), 1);
    // ASSERT_EQ(layout.at(4, 3).direction(), Tile::U_LEFT);
    // ASSERT_EQ(layout.at(4, 3).steps_to_castle(), 1);
    // ASSERT_EQ(layout.at(4, 4).direction(), Tile::LEFT);
    // ASSERT_EQ(layout.at(4, 4).steps_to_castle(), 2);
}

TEST(layout, contains){
    Layout layout(5, 5);
    ASSERT_TRUE(layout.contains(Coordinates(1, 1)));
    ASSERT_FALSE(layout.contains(Coordinates(5, 5)));
}