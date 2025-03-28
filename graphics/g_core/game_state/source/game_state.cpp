#include "game_state.hpp"

GameState& GameState::instance(){
    static GameState instance;
    return instance;
}
