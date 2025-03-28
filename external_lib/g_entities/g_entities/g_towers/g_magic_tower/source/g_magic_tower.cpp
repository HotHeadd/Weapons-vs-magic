#include "g_magic_tower.hpp"
#include "game_state.hpp"
#include "texture_manager.hpp"

GMagicTower::GMagicTower(ISystemManager& manager,
        IEffectFactory& factory,
        hp_t hp, 
        Coordinates position, 
        unsigned cost, 
        double vision_radius, 
        hp_t damage, 
        double rapidity, 
        std::vector<std::unordered_map<std::string, std::string>>& table,
        std::unordered_map<std::string, MagicNode>& magic_effects,
        const std::string& path_to_texture
    ) : MagicTower(manager, factory, hp, position, cost, vision_radius, damage, rapidity, table, magic_effects),
        tower_shape_(sf::Vector2f(GameState::instance().CELL_SIZE_X, GameState::instance().CELL_SIZE_Y)){
    texture_ = TextureManager::instance().get_texture(path_to_texture);
    tower_shape_.setTexture(texture_);
    radius_shape_.setFillColor(sf::Color::Transparent);
    radius_shape_.setOutlineThickness(2);
    sf::Color outlineColor = sf::Color(0, 0, 255, 160);
    radius_shape_.setOutlineColor(outlineColor);
}

sf::Texture* GMagicTower::texture(){
    return texture_;
}

void GMagicTower::render(){
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
