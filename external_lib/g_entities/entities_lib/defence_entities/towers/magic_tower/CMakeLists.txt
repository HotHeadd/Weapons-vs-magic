add_library(MagicTower)

target_link_libraries(MagicTower PUBLIC Tower)
target_include_directories(MagicTower PUBLIC include)
target_sources(MagicTower PRIVATE source/magic_tower.cpp)