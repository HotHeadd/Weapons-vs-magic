add_library(Towers INTERFACE)

add_subdirectory(tower)
add_subdirectory(magic_tower)

target_link_libraries(Towers INTERFACE Tower MagicTower)