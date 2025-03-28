#include "game.hpp"

#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>

namespace WVM
{

json Game::get_game_json(){
    json save_json = json::object({{"level_name", level_name}});
    save_json["lib_name"] = lib_name_;
    save_json["castle"] = system_manager_.get_castle().save();
    save_json["layout"] = system_manager_.get_layout().save();
    save_json["lairs"] = save_lairs();
    save_json["defence"] = save_defence();
    save_json["enemes"] = save_enemies();
    return save_json;
}

json Game::save_lairs(){
    json lairs_json = json::array();
    for (auto& lair : system_manager_.get_lairs()){
        lairs_json.push_back(lair->save());
    }
    return lairs_json;
}

json Game::save_defence(){
    json defence_json = json::array();
    return defence_json;
}

json Game::save_enemies(){
    json enemies_json = json::array();
    return enemies_json;
}

std::string get_local_share_path(){
    const char* home_path = std::getenv("HOME");
    if (!home_path){
        std::runtime_error("No Home");
    }
    return std::string(home_path) + "/.local/share/" + "wvm_game";
}

void Game::save(const std::string& filename){
    json save_file = get_game_json();
    std::string share_path = get_local_share_path();
    std::filesystem::create_directories(share_path);
    std::ofstream file(share_path + "/" + filename + ".json");
    file << save_file.dump(4);
    file.close();
}

void Game::save_script(const std::string& filename){
    json save_file = get_game_json();
    std::ofstream file(std::string("assets/scripts/") + filename + ".json");
    file << save_file.dump(4);
    file.close();
}

Game Game::load(const std::string& filename){
    json load_json = json::object();
    std::string share_path = get_local_share_path();
    std::ifstream file(share_path + "/" + filename + ".json");
    file >> load_json;
    return load_game_json(load_json);
}

Game Game::load_script(const std::string& filename){
    json load_json = json::object();
    std::ifstream file(std::string("assets/scripts/") + filename + ".json");
    file >> load_json;
    return load_game_json(load_json);
}

Game Game::load_game_json(json& save_json){
    std::shared_ptr<Layout> layout = Layout::load(save_json["layout"]);
    std::shared_ptr<Castle> castle = Castle::load(save_json["castle"]);
    std::string level_name = save_json["level_name"],
                plugin_lib_name = save_json["lib_name"];
    Game game(layout, castle, level_name);
    game.load_config(plugin_lib_name);
    json lairs_json = save_json["lairs"];
    json enemies_json = save_json["enemies"];
    json defence_json = save_json["defence"];
    game.load_lairs(lairs_json);
    game.load_defence(defence_json);
    game.load_enemies(enemies_json);
    return game;
}

void Game::load_lairs(json& lairs_json){
    for (auto& lair_json : lairs_json){
        Coordinates lair_pos(lair_json["x"], lair_json["y"]);
        std::shared_ptr<ILair> new_lair = add_empty_lair(lair_pos);
        if (!new_lair){
            throw std::runtime_error("Corrupted save file: double lair in same location");
        }
        new_lair->load(lair_json);
    }
}

void Game::load_defence(json& defence_json){

}

void Game::load_enemies(json& enemies_json){

}

} // namespace WVM