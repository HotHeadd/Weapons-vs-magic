add_library(GameState SHARED)

target_include_directories(GameState PUBLIC include)
target_sources(GameState PRIVATE source/game_state.cpp)