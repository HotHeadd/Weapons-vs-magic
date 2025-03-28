add_library(Game)

target_include_directories(Game PUBLIC include)

target_sources(Game PRIVATE source/game.cpp
                            source/game_persistence.cpp)

target_link_libraries(Game PUBLIC Systems Lair Factories stdc++fs)