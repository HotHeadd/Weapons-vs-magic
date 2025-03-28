add_library(TowerMenu)

target_include_directories(TowerMenu PUBLIC include)

target_sources(TowerMenu PRIVATE source/tower_menu.cpp)

target_link_libraries(TowerMenu PUBLIC GameState Game GNodes TextureManager)