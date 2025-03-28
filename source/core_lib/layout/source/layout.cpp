#include "layout.hpp"
#include <queue>
#include <set>
#include <array>

namespace WVM
{

Coordinates opposite_direction(Coordinates direction) {
    return {-direction.x, -direction.y};
}

Tile& Layout::operator() (const Coordinates& pos){
    return (*this)[pos.x][pos.y];
}

void Layout::calculate_paths(){
    std::queue<Coordinates> tile_queue;
    for (size_t i=0; i<this->rows(); i++){
        for (size_t j=0; j< this->columns(); j++){
            Tile& current_tile = this->at(i, j);
            if (current_tile.type() == TileType::CASTLE){
                current_tile.set_steps(0);
                tile_queue.emplace(i, j);
            }
        }
    }
    std::array<Coordinates, 8> directions = {Tile::UP, Tile::DOWN, Tile::LEFT, Tile::RIGHT}; //, Tile::U_LEFT, Tile::U_RIGHT, Tile::D_LEFT, Tile::D_RIGHT};
    // std::set<Coordinates> diag_directions = {Tile::D_LEFT, Tile::D_RIGHT, Tile::U_LEFT, Tile::U_RIGHT};
    while (!tile_queue.empty()){
        Coordinates curr_coords = tile_queue.front();
        tile_queue.pop();
        for (auto& diff : directions){
            Tile& current_tile = (*this)(curr_coords.x, curr_coords.y);
            Coordinates new_c = {curr_coords.x+diff.x, curr_coords.y+diff.y};
            if (contains(new_c)){
                Tile& diff_tile = (*this)(new_c);
                if (diff_tile.steps_to_castle() == Tile::UND_DIST and diff_tile.type() == TileType::ROAD){
                    diff_tile.set_steps(current_tile.steps_to_castle()+1);
                    diff_tile.set_direction(opposite_direction(diff));
                    tile_queue.push(new_c);
                }
                // if (diff_tile.steps_to_castle() == current_tile.steps_to_castle()+1 and diag_directions.contains(diff_tile.direction()) and
                //     !diag_directions.contains(diff)){
                //     diff_tile.set_direction(opposite_direction(diff));
                // }
            }
        }
    }
}

bool Layout::contains(const Coordinates& pos){
    return (0 <= pos.x and pos.x < rows()) and (0 <= pos.y and pos.y < columns());
}

json Layout::save(){
    json layout_json = json::object();
    std::string layout_string;
    layout_json["rows"] = rows_;
    layout_json["columns"] = columns_;
    for (auto& tile : *this){
        switch (tile.type()){
            case TileType::ROAD:
                layout_string += "R";
                break;
            case TileType::WALL:
                layout_string += "W";
                break;
            case TileType::FIELD:
                layout_string += "F";
                break;
            case TileType::CASTLE:
                layout_string += "C";
                break;
            default:
                throw std::logic_error("Undefined tile type on save");
        }
    }
    layout_json["state"] = layout_string;
    return layout_json;
}

std::shared_ptr<Layout> Layout::load(json& save_json){
    unsigned rows = save_json["rows"];
    unsigned columns = save_json["columns"];
    std::string state = save_json["state"];
    int i=0;
    std::shared_ptr<Layout> layout = std::make_shared<Layout>(rows, columns);
    for (auto& tile : *layout){
        if (i == state.size()){
            throw std::runtime_error("Corrupted save file (layout)");
        }
        switch (state[i]){
            case 'R':
                tile.set_type(TileType::ROAD);
                break;
            case 'W':
                tile.set_type(TileType::WALL);
                break;
            case 'F':
                tile.set_type(TileType::FIELD);
                break;
            case 'C':
                tile.set_type(TileType::CASTLE);
                break;
        }
        i++;
    }
    if (i != state.size()){
        throw std::runtime_error("Corrupted save file (layout)");
    }
    layout->calculate_paths();
    return layout;
}

} // namespace WVM
