#include "g_enemy.hpp"
#include "game_state.hpp"
#include "texture_manager.hpp"

GEnemy::GEnemy(
        ISystemManager& manager,
        hp_t max_hp, 
        double speed, 
        hp_t damage, 
        unsigned gold, 
        Coordinates position,
        const std::string& path_to_texture) 
            : Enemy(manager, max_hp, speed, damage, gold, position),
              enemy_shape_(sf::Vector2f(GameState::instance().CELL_SIZE_X, GameState::instance().CELL_SIZE_Y)){
    texture_ = TextureManager::instance().get_texture(path_to_texture);
    enemy_shape_.setTexture(texture_);
}

sf::Texture* GEnemy::texture(){
    return texture_;
}

void GEnemy::render(){
    enemy_shape_.setPosition(position_.y*GameState::instance().CELL_SIZE_X,
                             position_.x*GameState::instance().CELL_SIZE_Y);
    GameState::instance().draw_q.push(&enemy_shape_);
}
