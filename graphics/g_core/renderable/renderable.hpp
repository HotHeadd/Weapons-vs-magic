#pragma once

#include <SFML/Graphics.hpp>

class Renderable{
public:
    virtual void render() = 0;
    virtual sf::Texture* texture() = 0;
};