#pragma once
#include <SFML/Graphics.hpp>
#include <queue>

class GameState{
public:
    static GameState& instance();
    bool is_paused=false;
    bool display_attack=true;
    unsigned CELL_SIZE_X=1, CELL_SIZE_Y=1;
    std::queue<sf::Drawable*> draw_q;

    static constexpr double WINDOW_SIZE_X = 1000, WINDOW_SIZE_Y=1400;

    static constexpr unsigned LAYOUT_X = 1000, LAYOUT_Y = 1000;
    static constexpr unsigned OFFSET_X = LAYOUT_X, OFFSET_Y = 0;
    static constexpr unsigned BUTTON_SIZE_X = 200, BUTTON_SIZE_Y = 100;

    static constexpr unsigned INFO_SIZE_X = 390, INFO_SIZE_Y = 130;
    static constexpr unsigned MENU_SIZE_X = 390, MENU_SIZE_Y = 250;
private:
    GameState() = default;
};
