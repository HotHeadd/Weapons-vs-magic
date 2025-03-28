#include "tower_menu.hpp"
#include "game_state.hpp"
#include "texture_manager.hpp"

TowerButton::TowerButton(const std::string& name, GTowerNode& node, unsigned y_offset, sf::RenderWindow& window, Game& game) :
                        window_(window), game_(game), tower_cost(node.cost), tower_name(name) {
    button_shape.setPosition(GameState::OFFSET_X+10, y_offset);
    button_shape.setSize(sf::Vector2f(GameState::MENU_SIZE_X-10, 50));
    button_shape.setFillColor(sf::Color::White);
    button_shape.setOutlineThickness(2);
    button_shape.setOutlineColor(sf::Color::Black); 

    tower_shape.setSize(sf::Vector2f(40, 40));
    tower_shape.setPosition(GameState::OFFSET_X+15, y_offset+5);
    tower_shape.setTexture(TextureManager::instance().get_texture(node.texture_path));

    tower_text.setFont(TextureManager::instance().get_font("assets/fonts/comic_sans.ttf"));
    tower_text.setCharacterSize(30);
    tower_text.setFillColor(sf::Color::Black);
    tower_text.setPosition(GameState::OFFSET_X+60, y_offset+5);
    tower_text.setString(name + " : " + std::to_string(tower_cost));
}

bool TowerButton::is_enough(){
    return game_.castle().enough(tower_cost);
}

void TowerButton::draw(){
    if (is_selected){
        button_shape.setOutlineColor(sf::Color::Yellow);
    }
    else if (is_enough()){
        button_shape.setOutlineColor(sf::Color::Green);
    }
    else{
        button_shape.setOutlineColor(sf::Color::Red);
    }
    window_.draw(button_shape);
    window_.draw(tower_shape);
    window_.draw(tower_text);
}

TowerMenu::TowerMenu(Game& game, sf::RenderWindow& window) : 
        game_(game), window_(window), outliner(sf::Vector2f(GameState::MENU_SIZE_X, GameState::MENU_SIZE_Y)) {
    offset_x = GameState::OFFSET_X+5;
    offset_y = GameState::OFFSET_Y + GameState::BUTTON_SIZE_Y+GameState::INFO_SIZE_Y+10;

    outliner.setPosition(offset_x, offset_y);
    outliner.setFillColor(sf::Color::White);
    outliner.setOutlineThickness(5);
    outliner.setOutlineColor(sf::Color::Black); 

    intro_text.setPosition(offset_x+5, offset_y);
    intro_text.setFont(TextureManager::instance().get_font("assets/fonts/comic_sans.ttf"));
    intro_text.setCharacterSize(30);
    intro_text.setFillColor(sf::Color::Black);
    intro_text.setString("Tower menu");

    unsigned temp_y = offset_y + 45;
    for (auto& tower_pair : game_.list_all_towers()){
        GTowerNode& gnode = static_cast<GTowerNode&>(*tower_pair.second);
        TowerButton button(tower_pair.first, gnode, temp_y, window_, game_);
        buttons.push_back(std::move(button));
        temp_y += 56;
    }
}

void TowerMenu::draw(){
    window_.draw(outliner);
    unsigned temp_offset_y = offset_y;
    window_.draw(intro_text);
    for (auto& button : buttons){
        button.draw();
    }
}

bool TowerMenu::is_clicked(sf::Vector2f& mouse_pos){
    return outliner.getGlobalBounds().contains(mouse_pos);
}

bool TowerButton::is_clicked(sf::Vector2f& mouse_pos){
    return button_shape.getGlobalBounds().contains(mouse_pos);
}

void TowerMenu::process_click(sf::Vector2f& mouse_pos){
    if (is_clicked(mouse_pos)){
        for (auto& button : buttons){
            if (button.is_clicked(mouse_pos) and button.is_enough()){
                button.is_selected = true;
            }
            else{
                button.is_selected = false;
            }
        }
    }
    else{
        for (auto& button : buttons){
            if (button.is_selected){
                Coordinates coords = deduct_tile(mouse_pos);
                if (game_.layout().contains(coords) and game_.layout()(coords).type() == TileType::FIELD and is_free_tile(coords)){
                    game_.castle().decrease_gold(button.tower_cost);
                    game_.add_tower(button.tower_name, coords);
                }
                button.is_selected = false;
            }
        }
    }
}

bool TowerMenu::is_free_tile(const Coordinates& coords){
    for (auto& def : game_.get_sys_manager().get_defence()){
        if (def->position() == coords){
            return false;
        }
    }
    return true;
}

Coordinates TowerMenu::deduct_tile(sf::Vector2f& mouse_pos){
    int tile_y = mouse_pos.x/GameState::instance().CELL_SIZE_Y;
    int tile_x = mouse_pos.y/GameState::instance().CELL_SIZE_X;
    return {tile_x, tile_y};
}