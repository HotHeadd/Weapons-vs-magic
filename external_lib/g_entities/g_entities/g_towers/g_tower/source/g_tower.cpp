#include "g_tower.hpp"
#include "game_state.hpp"
#include "texture_manager.hpp"

GTower::GTower(ISystemManager& manager,
        hp_t hp,
        Coordinates position, 
        unsigned cost, 
        double vision_radius, 
        hp_t damage, 
        double rapidity, 
        std::vector<std::unordered_map<std::string, std::string>>& table,
        const std::string& path_to_texture) : 
            Tower(manager, hp, position, cost, vision_radius, damage, rapidity, table),
            tower_shape_(sf::Vector2f(GameState::instance().CELL_SIZE_X, GameState::instance().CELL_SIZE_Y)){
    texture_ = TextureManager::instance().get_texture(path_to_texture);
    tower_shape_.setTexture(texture_);
    radius_shape_.setFillColor(sf::Color::Transparent);
    radius_shape_.setOutlineThickness(2);
    sf::Color outlineColor = sf::Color(255, 0, 0, 160);
    radius_shape_.setOutlineColor(outlineColor);
}

sf::Texture* GTower::texture(){
    return texture_;
}

void GTower::render(){
    tower_shape_.setPosition(position_.y*GameState::instance().CELL_SIZE_X,
                             position_.x*GameState::instance().CELL_SIZE_Y);
    GameState::instance().draw_q.push(&tower_shape_);
    if (GameState::instance().display_attack){
        double radius = GameState::instance().CELL_SIZE_X*(vision_radius_);
        radius_shape_.setRadius(radius);
        radius_shape_.setPosition(
            ((double)position_.y+0.5)*GameState::instance().CELL_SIZE_X - radius,
            ((double)position_.x+0.5)*GameState::instance().CELL_SIZE_Y - radius
        );
        GameState::instance().draw_q.push(&radius_shape_);
    }
}
