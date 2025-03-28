#include "drawfuncs.hpp"
#include <random>
#include "game.hpp"

std::shared_ptr<Layout> generate_random_layout(size_t x_size, size_t y_size){
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_int_distribution<std::mt19937::result_type> dist6(1,7);
    std::shared_ptr<Layout> layout = std::make_shared<Layout>(x_size, y_size);
    for (int x = 0; x<x_size; x++){
        for (int y=0; y<y_size; y++){
            switch (dist6(rng))
            {
            case 1:
                layout->at(x, y).set_type(TileType::ROAD);
                break;
            case 2:
                layout->at(x, y).set_type(TileType::ROAD);
                break;
            case 3:
                layout->at(x, y).set_type(TileType::ROAD);
                break;
            case 4:
                layout->at(x, y).set_type(TileType::CASTLE);
                break;
            case 5:
                layout->at(x, y).set_type(TileType::WALL);
                break;
            case 6:
                layout->at(x, y).set_type(TileType::FIELD);
                break;
            case 7:
                layout->at(x, y).set_type(TileType::ROAD);
                break;
            }
        }
    }
    return layout;
}

std::shared_ptr<Layout> setup_layout_big(){
    std::shared_ptr<Layout> layout = std::make_shared<Layout>(10, 10);
    layout->at(1, 0).set_type(TileType::WALL);
    layout->at(1, 1).set_type(TileType::WALL);
    layout->at(1, 2).set_type(TileType::FIELD);
    layout->at(1, 3).set_type(TileType::WALL);
    layout->at(1, 4).set_type(TileType::WALL);
    layout->at(1, 5).set_type(TileType::WALL);
    layout->at(1, 6).set_type(TileType::WALL);
    layout->at(1, 7).set_type(TileType::WALL);
    layout->at(1, 8).set_type(TileType::WALL);
    layout->at(6, 2).set_type(TileType::WALL);
    layout->at(6, 3).set_type(TileType::WALL);
    layout->at(6, 4).set_type(TileType::WALL);
    layout->at(6, 5).set_type(TileType::WALL);
    layout->at(6, 6).set_type(TileType::WALL);
    layout->at(6, 7).set_type(TileType::WALL);
    layout->at(6, 8).set_type(TileType::WALL);
    layout->at(6, 9).set_type(TileType::WALL);
    layout->at(7, 2).set_type(TileType::WALL);
    layout->at(8, 7).set_type(TileType::WALL);
    layout->at(9, 7).set_type(TileType::WALL);
    layout->at(6, 4).set_type(TileType::FIELD);

    layout->at(8, 0).set_type(TileType::CASTLE);
    layout->at(8, 1).set_type(TileType::CASTLE);
    layout->at(9, 0).set_type(TileType::CASTLE);
    layout->at(9, 1).set_type(TileType::CASTLE);
    layout->calculate_paths();
    return layout;
}

std::shared_ptr<Layout> setup_layout_smoll(){
    std::shared_ptr<Layout> layout = std::make_shared<Layout>(5, 5);
    layout->at(1, 0).set_type(TileType::WALL);
    layout->at(1, 2).set_type(TileType::WALL);
    layout->at(1, 3).set_type(TileType::WALL);
    layout->at(3, 3).set_type(TileType::WALL);
    layout->at(1, 1).set_type(TileType::FIELD);
    layout->at(3, 1).set_type(TileType::CASTLE);
    layout->at(3, 2).set_type(TileType::CASTLE);
    layout->calculate_paths();
    return layout;
}

std::shared_ptr<Layout> setup_layout_huge(){
    std::shared_ptr<Layout> layout = std::make_shared<Layout>(20, 20);
    layout->fill(Tile(TileType::WALL));
    layout->fill_row(0, Tile(TileType::ROAD));
    layout->fill_row(19, Tile(TileType::ROAD));
    layout->fill_column(11, Tile(TileType::ROAD));
    layout->fill_column(8, Tile(TileType::ROAD));
    layout->fill_column(2, Tile(TileType::ROAD));
    layout->fill_column(17, Tile(TileType::ROAD));
    layout->fill_row(5, Tile(TileType::ROAD));
    layout->fill_row(14, Tile(TileType::ROAD));
    layout->fill_row(8, Tile(TileType::ROAD));
    layout->fill_row(10, Tile(TileType::ROAD));

    layout->at(5, 0).set_type(TileType::WALL);
    layout->at(5, 1).set_type(TileType::WALL);
    layout->at(5, 19).set_type(TileType::WALL);
    layout->at(5, 18).set_type(TileType::WALL);
    layout->at(8, 0).set_type(TileType::WALL);
    layout->at(8, 1).set_type(TileType::WALL);
    layout->at(8, 19).set_type(TileType::WALL);
    layout->at(8, 18).set_type(TileType::WALL);
    layout->at(10, 0).set_type(TileType::WALL);
    layout->at(10, 1).set_type(TileType::WALL);
    layout->at(10, 19).set_type(TileType::WALL);
    layout->at(10, 18).set_type(TileType::WALL);
    layout->at(14, 0).set_type(TileType::WALL);
    layout->at(14, 1).set_type(TileType::WALL);
    layout->at(14, 19).set_type(TileType::WALL);
    layout->at(14, 18).set_type(TileType::WALL);

    layout->at(1, 2).set_type(TileType::WALL);
    layout->at(2, 2).set_type(TileType::WALL);
    layout->at(3, 2).set_type(TileType::WALL);
    layout->at(4, 2).set_type(TileType::WALL);
    layout->at(1, 17).set_type(TileType::WALL);
    layout->at(2, 17).set_type(TileType::WALL);
    layout->at(3, 17).set_type(TileType::WALL);
    layout->at(4, 17).set_type(TileType::WALL);

    layout->at(18, 2).set_type(TileType::WALL);
    layout->at(17, 2).set_type(TileType::WALL);
    layout->at(16, 2).set_type(TileType::WALL);
    layout->at(15, 2).set_type(TileType::WALL);
    layout->at(18, 17).set_type(TileType::WALL);
    layout->at(17, 17).set_type(TileType::WALL);
    layout->at(16, 17).set_type(TileType::WALL);
    layout->at(15, 17).set_type(TileType::WALL);

    layout->at(9, 2).set_type(TileType::WALL);
    layout->at(9, 17).set_type(TileType::WALL);

    layout->at(13, 8).set_type(TileType::WALL);
    layout->at(13, 11).set_type(TileType::WALL);
    layout->at(12, 8).set_type(TileType::WALL);
    layout->at(12, 11).set_type(TileType::WALL);
    layout->at(7, 8).set_type(TileType::WALL);
    layout->at(11, 8).set_type(TileType::WALL);
    layout->at(11, 11).set_type(TileType::WALL);
    layout->at(7, 11).set_type(TileType::WALL);
    layout->at(6, 8).set_type(TileType::WALL);
    layout->at(6, 11).set_type(TileType::WALL);

    layout->at(9, 9).set_type(TileType::CASTLE);
    layout->at(9, 8).set_type(TileType::CASTLE);
    layout->at(9, 10).set_type(TileType::CASTLE);
    layout->at(8, 9).set_type(TileType::CASTLE);
    layout->at(8, 8).set_type(TileType::CASTLE);
    layout->at(8, 10).set_type(TileType::CASTLE);
    layout->at(10, 9).set_type(TileType::CASTLE);
    layout->at(10, 8).set_type(TileType::CASTLE);
    layout->at(10, 10).set_type(TileType::CASTLE);
    layout->at(10, 11).set_type(TileType::CASTLE);
    layout->at(9, 11).set_type(TileType::CASTLE);
    layout->at(8, 11).set_type(TileType::CASTLE);

    layout->at(2, 6).set_type(TileType::FIELD);
    layout->at(2, 13).set_type(TileType::FIELD);
    layout->at(2, 1).set_type(TileType::FIELD);
    layout->at(2, 18).set_type(TileType::FIELD);
    layout->at(2, 9).set_type(TileType::FIELD);
    layout->at(2, 10).set_type(TileType::FIELD);

    layout->at(1, 4).set_type(TileType::FIELD);
    layout->at(1, 15).set_type(TileType::FIELD);
    layout->at(4, 5).set_type(TileType::FIELD);
    layout->at(4, 14).set_type(TileType::FIELD);

    layout->at(6, 8).set_type(TileType::FIELD);
    layout->at(6, 11).set_type(TileType::FIELD);
    layout->at(6, 5).set_type(TileType::FIELD);
    layout->at(6, 14).set_type(TileType::FIELD);
    layout->at(6, 1).set_type(TileType::FIELD);
    layout->at(6, 18).set_type(TileType::FIELD);

    layout->at(7, 4).set_type(TileType::FIELD);
    layout->at(7, 15).set_type(TileType::FIELD);

    layout->at(9, 6).set_type(TileType::FIELD);
    layout->at(9, 3).set_type(TileType::FIELD);
    layout->at(9, 16).set_type(TileType::FIELD);
    layout->at(9, 13).set_type(TileType::FIELD);

    layout->at(11, 1).set_type(TileType::FIELD);
    layout->at(11, 18).set_type(TileType::FIELD);
    layout->at(11, 5).set_type(TileType::FIELD);
    layout->at(11, 14).set_type(TileType::FIELD);

    layout->at(13, 1).set_type(TileType::FIELD);
    layout->at(13, 18).set_type(TileType::FIELD);
    layout->at(13, 4).set_type(TileType::FIELD);
    layout->at(13, 15).set_type(TileType::FIELD);
    layout->at(13, 7).set_type(TileType::FIELD);
    layout->at(13, 12).set_type(TileType::FIELD);

    layout->at(15, 3).set_type(TileType::FIELD);
    layout->at(15, 9).set_type(TileType::FIELD);
    layout->at(15, 10).set_type(TileType::FIELD);
    layout->at(15, 16).set_type(TileType::FIELD);

    layout->at(16, 6).set_type(TileType::FIELD);
    layout->at(16, 13).set_type(TileType::FIELD);
    layout->at(17, 4).set_type(TileType::FIELD);
    layout->at(17, 15).set_type(TileType::FIELD);
    layout->at(18, 7).set_type(TileType::FIELD);
    layout->at(18, 12).set_type(TileType::FIELD);

    layout->calculate_paths();
    return layout;
}