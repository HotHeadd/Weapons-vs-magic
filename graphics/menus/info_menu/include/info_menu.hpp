#pragma once

#include <SFML/Graphics.hpp>
#include "game.hpp"

using namespace WVM;

class InfoMenu{
public:
    InfoMenu(Game& game, sf::RenderWindow& window) : game_(game), window_(window) {}
    void draw();
private:
    Game& game_;
    sf::RenderWindow& window_;
};