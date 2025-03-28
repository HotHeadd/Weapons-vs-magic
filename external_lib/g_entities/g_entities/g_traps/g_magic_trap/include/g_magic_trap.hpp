#pragma once

#include <SFML/Graphics.hpp>
#include "magic_trap.hpp"
#include "renderable.hpp"

using namespace WVM;

class GMagicTrap : public MagicTrap, public Renderable {
public:
    GMagicTrap(
        ISystemManager& manager,
        IEffectFactory& factory,
        Coordinates position,
        unsigned cost,
        double vision_radius,
        double effect_radius,
        hp_t damage,
        std::unordered_map<std::string, MagicNode>& magic_effects,
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
