add_library(TrapMenu)

target_include_directories(TrapMenu PUBLIC include)

target_sources(TrapMenu PRIVATE source/trap_menu.cpp)

target_link_libraries(TrapMenu PUBLIC Game GameState TextureManager GNodes)