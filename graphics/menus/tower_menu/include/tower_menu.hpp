#pragma once

#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "g_nodes.hpp"
#include <vector>

using namespace WVM;

class TowerButton{
public:
    TowerButton(const std::string&, GTowerNode&, unsigned, sf::RenderWindow&, Game& game);
    void draw();

    bool is_selected=false;

    bool is_clicked(sf::Vector2f& mouse_pos);
    bool is_enough();
private:
    sf::RectangleShape button_shape;
    sf::RectangleShape tower_shape;
    sf::Text tower_text;
    unsigned tower_cost;
    std::string tower_name;

    sf::RenderWindow& window_;
    Game& game_;
    friend class TowerMenu;
};

class TowerMenu{
public:
    TowerMenu(Game& game, sf::RenderWindow& window);
    void draw();

    bool is_clicked(sf::Vector2f& mouse_pos);
    void process_click(sf::Vector2f& mouse_pos);
private:
    Coordinates deduct_tile(sf::Vector2f& mouse_pos);
    bool is_free_tile(const Coordinates& coords);

    sf::RectangleShape outliner;
    unsigned offset_x, offset_y;
    sf::Text intro_text;

    Game& game_;
    sf::RenderWindow& window_;

    std::vector<TowerButton> buttons;
};