add_library(GEnemy)

target_include_directories(GEnemy PUBLIC include)

target_sources(GEnemy PRIVATE source/g_enemy.cpp)

target_link_libraries(GEnemy PUBLIC Enemy Renderable GameState TextureManager)