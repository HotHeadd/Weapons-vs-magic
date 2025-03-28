#include "render_manager.hpp"
#include "drawfuncs.hpp"
#include "renderable.hpp"
#include "game_state.hpp"
#include "g_nodes.hpp"


#include "texture_manager.hpp"

RenderManager::RenderManager(Game& game) : 
        game_(game), window_(sf::VideoMode(GameState::WINDOW_SIZE_Y, GameState::WINDOW_SIZE_X), game.level_name),
        tower_menu(game, window_), trap_menu(game, window_), info_menu(game, window_) {
    GameState::instance().CELL_SIZE_X = GameState::LAYOUT_X/game.layout().rows();
    GameState::instance().CELL_SIZE_Y = GameState::LAYOUT_Y/game.layout().columns();
    CELL_SIZE_X = GameState::instance().CELL_SIZE_X;
    CELL_SIZE_Y = GameState::instance().CELL_SIZE_Y;

    window_.setPosition(sf::Vector2i(0, 0));
    pause_button.setPosition(sf::Vector2f(GameState::OFFSET_X, GameState::OFFSET_Y));
    pause_button.setSize(sf::Vector2f(GameState::BUTTON_SIZE_X, GameState::BUTTON_SIZE_Y));
    display_button.setPosition(sf::Vector2f(GameState::OFFSET_X+GameState::BUTTON_SIZE_X, GameState::OFFSET_Y));
    display_button.setSize(sf::Vector2f(GameState::BUTTON_SIZE_X, GameState::BUTTON_SIZE_Y));

    lair_shape.setSize(sf::Vector2f(CELL_SIZE_X, CELL_SIZE_Y));
    sf::Texture* lair_texture = TextureManager::instance().get_texture("assets/textures/entities/lair.png");
    lair_shape.setTexture(lair_texture);

    game_over_shape.setSize(sf::Vector2f(1000, 750));
    game_over_shape.setTexture(TextureManager::instance().get_texture("assets/textures/other/gameover.png"));
    game_over_shape.setPosition(sf::Vector2f(0, 180));
}

void RenderManager::start_game_loop(unsigned updates_per_sec){
    double time_step = 1.0f/updates_per_sec;
    sf::Clock clock;
    double accumulated_time = 0.0;

    while (window_.isOpen()) {
        handle_events();
        window_.clear(sf::Color::White);
        
        double elapsed_time = clock.restart().asSeconds();
        accumulated_time += elapsed_time;

        while (accumulated_time >= time_step) {
            if (!GameState::instance().is_paused) {
                game_.update();
            }
            accumulated_time -= time_step;
        }

        draw_layout();
        draw_entities();
        draw_general_info();
        draw_buttons();

        tower_menu.draw();
        trap_menu.draw();
        info_menu.draw();

        if (game_.game_over()){
            draw_game_over();
        }

        window_.display();
    }
}

void RenderManager::handle_events(){
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed){
            window_.close();
        }
        if (event.type == sf::Event::KeyPressed){
            if (event.key.code == sf::Keyboard::Escape){
                window_.close();
            }
            if (event.key.code == sf::Keyboard::P){
                GameState::instance().is_paused = !GameState::instance().is_paused;
            }
            if (event.key.code == sf::Keyboard::H){
                GameState::instance().display_attack = !GameState::instance().display_attack;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed){
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_);
            sf::Vector2f mouse_pos_f(mouse_pos.x, mouse_pos.y);
            if (pause_button.getGlobalBounds().contains(mouse_pos_f)){
                GameState::instance().is_paused = !GameState::instance().is_paused;
            }
            if (display_button.getGlobalBounds().contains(mouse_pos_f)){
                GameState::instance().display_attack = !GameState::instance().display_attack;
            }
            tower_menu.process_click(mouse_pos_f);
            trap_menu.process_click(mouse_pos_f);
        }
    }
    if (game_.game_over()){
        GameState::instance().is_paused = true;
        GameState::instance().display_attack = true;
    }
}

void RenderManager::draw_entities(){
    for (auto& enemy : game_.get_sys_manager().get_enemies()){
        if (auto r_enemy = std::dynamic_pointer_cast<Renderable>(enemy)){
            r_enemy->render();
        }
    }

    for (auto& lair : game_.get_sys_manager().get_lairs()){
        lair_shape.setPosition(lair->position().y*CELL_SIZE_X, lair->position().x*CELL_SIZE_Y);
        window_.draw(lair_shape);
    }

    for (auto& tower : game_.get_sys_manager().get_defence()){
        if (auto r_tower = std::dynamic_pointer_cast<Renderable>(tower)){
            r_tower->render();
        }
    }

    while (!GameState::instance().draw_q.empty()){
        sf::Drawable* shape = GameState::instance().draw_q.front();
        GameState::instance().draw_q.pop();
        window_.draw(*shape);
    }
}

void RenderManager::draw_layout(){
    Layout& layout = game_.layout();
    static sf::Texture road_texture, forest_texture, field_texture, castle_texture;
    static bool first_time=true;
    if (first_time){
        road_texture.loadFromFile("assets/textures/tiles/road.jpg");
        forest_texture.loadFromFile("assets/textures/tiles/wall.jpg");
        castle_texture.loadFromFile("assets/textures/tiles/castle.jpg");
        field_texture.loadFromFile("assets/textures/tiles/field.png");
        first_time = false;
    }

    for (int y = 0; y < layout.rows(); y++){
        for (int x = 0; x < layout.columns(); x++){
            sf::RectangleShape tile(sf::Vector2f(CELL_SIZE_X, CELL_SIZE_Y));
            switch (layout(x, y).type()) {
                case TileType::ROAD :  tile.setTexture(&road_texture); break;
                case TileType::FIELD : tile.setTexture(&field_texture); break;
                case TileType::WALL : tile.setTexture(&forest_texture); break;
                case TileType::CASTLE : tile.setTexture(&castle_texture); break;
            }
            tile.setPosition(y*CELL_SIZE_X, x*CELL_SIZE_Y);
            window_.draw(tile);
        }
    }
}

void RenderManager::draw_general_info(){
    static unsigned offset_x = GameState::OFFSET_X+5, offset_y = GameState::OFFSET_Y+GameState::BUTTON_SIZE_Y+5;
    static sf::Text castle_hp_text;
    static sf::RectangleShape outliner(sf::Vector2f(GameState::INFO_SIZE_X, GameState::INFO_SIZE_Y));
    static bool first_time = true;
    if (first_time){
        first_time = false;
        castle_hp_text.setFont(TextureManager::instance().get_font("assets/fonts/comic_sans.ttf"));
        castle_hp_text.setCharacterSize(30);
        castle_hp_text.setFillColor(sf::Color::Black);
        outliner.setPosition(offset_x, offset_y);
        outliner.setFillColor(sf::Color::White);
        outliner.setOutlineThickness(5);
        outliner.setOutlineColor(sf::Color::Black);
        castle_hp_text.setPosition(offset_x+10, offset_y);
    }
    Castle& castle = game_.castle();
    std::string castle_info = "Castle hp: " + std::to_string(static_cast<int>(castle.hp())) + 
                              "\nCastle gold: " + std::to_string(castle.gold()) + 
                              "\nCurrent wave: " + std::to_string(game_.current_wave());
    castle_hp_text.setString(castle_info);

    window_.draw(outliner);
    window_.draw(castle_hp_text);
}

void RenderManager::draw_buttons(){
    static sf::Texture paused, playing, hidden, displayed;
    static bool first_time = true;
    if (first_time){
        first_time = false;
        playing.loadFromFile("assets/textures/buttons/pause.png");      
        paused.loadFromFile("assets/textures/buttons/continue.png");       
        hidden.loadFromFile("assets/textures/buttons/show_attack.png");       
        displayed.loadFromFile("assets/textures/buttons/hide_attack.png");       
    }
    if (GameState::instance().is_paused){
        pause_button.setTexture(&paused);
    }
    else{
        pause_button.setTexture(&playing);
    }
    if (GameState::instance().display_attack){
        display_button.setTexture(&displayed);
    }
    else{
        display_button.setTexture(&hidden);
    }
    window_.draw(pause_button);
    window_.draw(display_button);
}

void RenderManager::draw_game_over(){
    window_.draw(game_over_shape);
}