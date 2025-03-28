#pragma once

#include <SFML/Graphics.hpp>
#include "magic_tower.hpp"
#include "renderable.hpp"

using namespace WVM;

class GMagicTower : public MagicTower, public Renderable{
public:
    GMagicTower(ISystemManager& manager,
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
    );
    void render() override;
    sf::Texture* texture() override;
private:
    sf::Texture* texture_;
    sf::RectangleShape tower_shape_;
    sf::CircleShape radius_shape_;
};
