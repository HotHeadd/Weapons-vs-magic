#pragma once

#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "tower_menu.hpp"
#include "trap_menu.hpp"
#include "info_menu.hpp"

using namespace WVM;

class RenderManager{
public:
    RenderManager(Game& game);
    void start_game_loop(unsigned updates_per_sec);
private:
    void handle_events();
    void draw_layout();
    void draw_entities();
    void draw_general_info();
    void draw_buttons();
    void draw_game_over();

    Game& game_;
    sf::RenderWindow window_;

    size_t CELL_SIZE_X, CELL_SIZE_Y;

    sf::RectangleShape pause_button;
    sf::RectangleShape display_button;
    sf::RectangleShape lair_shape;
    sf::RectangleShape game_over_shape;

    TowerMenu tower_menu;
    TrapMenu trap_menu;
    InfoMenu info_menu;
};