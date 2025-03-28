add_library(GMagicTrap)

target_include_directories(GMagicTrap PUBLIC include)

target_sources(GMagicTrap PRIVATE source/g_magic_trap.cpp)

target_link_libraries(GMagicTrap PUBLIC MagicTrap Renderable GameState TextureManager)