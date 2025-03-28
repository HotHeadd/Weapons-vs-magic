#include "info_menu.hpp"
#include "game_state.hpp"
#include "texture_manager.hpp"

void InfoMenu::draw(){
    unsigned offset_x = GameState::OFFSET_X+5, 
             offset_y = GameState::OFFSET_Y+GameState::BUTTON_SIZE_Y+
                        GameState::INFO_SIZE_Y+GameState::MENU_SIZE_Y*2+15;
    static sf::Text text;
    static sf::RectangleShape outliner(sf::Vector2f(GameState::MENU_SIZE_X, 250));
    static bool first_time = true;
    if (first_time){
        first_time = false;
        text.setFont(TextureManager::instance().get_font("assets/fonts/comic_sans.ttf"));
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Black);
        outliner.setPosition(offset_x, offset_y);
        outliner.setFillColor(sf::Color::White);
        outliner.setOutlineThickness(5);
        outliner.setOutlineColor(sf::Color::Black); 
    }
    window_.draw(outliner);
    text.setPosition(offset_x+10, offset_y);
    text.setString("I am info menu");
    window_.draw(text);
}