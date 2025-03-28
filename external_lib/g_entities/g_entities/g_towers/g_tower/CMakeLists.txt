add_library(GTower)

target_include_directories(GTower PUBLIC include)

target_sources(GTower PRIVATE source/g_tower.cpp)

target_link_libraries(GTower PUBLIC Tower Renderable GameState TextureManager)