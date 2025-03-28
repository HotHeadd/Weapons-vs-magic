#pragma once

#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "g_nodes.hpp"
#include <vector>

using namespace WVM;

class TrapButton {
public:
    TrapButton(const std::string& name, GTrapNode& node,
               unsigned y_offset, sf::RenderWindow& window, Game& game);

    void draw();

    bool is_selected=false;

    bool is_clicked(sf::Vector2f& mouse_pos);
    bool is_enough();
private:
    sf::RectangleShape button_shape;
    sf::RectangleShape trap_shape;
    sf::Text trap_text;
    unsigned trap_cost;
    unsigned trap_levelup_cost;
    unsigned trap_level=1;
    unsigned trap_max_level;
    std::string trap_name;

    Game& game_;
    sf::RenderWindow& window_;
    friend class TrapMenu;
};

class TrapMenu{
public:
    TrapMenu(Game& game, sf::RenderWindow& window);
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

    std::vector<TrapButton> buttons;
};