#include "g_trap.hpp"
#include "game_state.hpp"
#include "texture_manager.hpp"

GTrap::GTrap(
        ISystemManager& manager,
        Coordinates position,
        unsigned cost,
        double vision_radius,
        double effect_radius,
        hp_t damage,
        const std::string& path_to_texture) :
            Trap(manager, position, cost, vision_radius, effect_radius, damage), 
            trap_shape_(sf::Vector2f(GameState::instance().CELL_SIZE_X, GameState::instance().CELL_SIZE_Y)){
    texture_ = TextureManager::instance().get_texture(path_to_texture);
    trap_shape_.setTexture(texture_);

    radius_shape_.setFillColor(sf::Color::Transparent);
    effect_rad_shape_.setFillColor(sf::Color::Transparent);

    radius_shape_.setOutlineThickness(2);
    effect_rad_shape_.setOutlineThickness(2);

    sf::Color outlineColor_rad = sf::Color(0, 255, 0, 160);
    sf::Color outlineColor_eff = sf::Color(255, 0, 0, 160);

    radius_shape_.setOutlineColor(outlineColor_rad);
    effect_rad_shape_.setOutlineColor(outlineColor_eff);
}

sf::Texture* GTrap::texture(){
    return texture_;
}

void GTrap::render(){
    trap_shape_.setPosition(position_.y*GameState::instance().CELL_SIZE_X,
                             position_.x*GameState::instance().CELL_SIZE_Y);
    GameState::instance().draw_q.push(&trap_shape_);
    if (GameState::instance().display_attack){
        double radius = GameState::instance().CELL_SIZE_X*(vision_radius_);
        radius_shape_.setRadius(radius);
        radius_shape_.setPosition(
            ((double)position_.y+0.5)*GameState::instance().CELL_SIZE_X - radius,
            ((double)position_.x+0.5)*GameState::instance().CELL_SIZE_Y - radius
        );
        GameState::instance().draw_q.push(&radius_shape_);

        double radius_eff = GameState::instance().CELL_SIZE_X*(effect_radius_);
        effect_rad_shape_.setRadius(radius_eff);
        effect_rad_shape_.setPosition(
            ((double)position_.y+0.5)*GameState::instance().CELL_SIZE_X - radius_eff,
            ((double)position_.x+0.5)*GameState::instance().CELL_SIZE_Y - radius_eff
        );
        GameState::instance().draw_q.push(&effect_rad_shape_);
    }
}

