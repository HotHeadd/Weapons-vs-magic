#pragma once

#include <SFML/Graphics.hpp>
#include "tower.hpp"
#include "renderable.hpp"

using namespace WVM;

class GTower : public Tower, public Renderable{
public:
    GTower(ISystemManager& manager,
        hp_t hp, 
        Coordinates position, 
        unsigned cost, 
        double vision_radius, 
        hp_t damage, 
        double rapidity, 
        std::vector<std::unordered_map<std::string, std::string>>& table,
        const std::string& path_to_texture
    );
    void render() override;
    sf::Texture* texture() override;
private:
    sf::Texture* texture_;
    sf::RectangleShape tower_shape_;
    sf::CircleShape radius_shape_;
};