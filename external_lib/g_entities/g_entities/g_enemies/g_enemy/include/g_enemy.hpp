#pragma once

#include <SFML/Graphics.hpp>
#include "enemy.hpp"
#include "renderable.hpp"

using namespace WVM;

class GEnemy : public Enemy, public Renderable{
public:
    GEnemy(ISystemManager& manager,
            hp_t max_hp, 
            double speed, 
            hp_t damage, 
            unsigned gold, 
            Coordinates position,
            const std::string& path_to_texture
    );
    void render() override;
    sf::Texture* texture() override;
private:
    sf::Texture* texture_;
    sf::RectangleShape enemy_shape_;
};