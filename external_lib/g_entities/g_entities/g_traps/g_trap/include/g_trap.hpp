#pragma once

#include <SFML/Graphics.hpp>
#include "trap.hpp"
#include "renderable.hpp"

using namespace WVM;

class GTrap : public Trap, public Renderable{
public:
    GTrap(
        ISystemManager& manager,
        Coordinates position,
        unsigned cost,
        double vision_radius,
        double effect_radius,
        hp_t damage,
        const std::string& path_to_texture
    );
    void render() override;
    sf::Texture* texture() override;
private:
    sf::Texture* texture_;
    sf::RectangleShape trap_shape_;
    sf::CircleShape radius_shape_;
    sf::CircleShape effect_rad_shape_;
};