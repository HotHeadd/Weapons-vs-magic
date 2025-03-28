add_library(GMagicTower)

target_include_directories(GMagicTower PUBLIC include)

target_sources(GMagicTower PRIVATE source/g_magic_tower.cpp)

target_link_libraries(GMagicTower PUBLIC MagicTower Renderable GameState TextureManager)