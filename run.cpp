#include <SFML/Graphics.hpp>
#include "game.hpp"

#include "render_manager.hpp"

using namespace WVM;

int main(){
    Game game = Game::load_script("Main scenario");
    RenderManager render_man(game);

    render_man.start_game_loop(20);
}