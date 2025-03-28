add_library(InfoMenu)

target_include_directories(InfoMenu PUBLIC include)

target_sources(InfoMenu PRIVATE source/info_menu.cpp)

target_link_libraries(InfoMenu PUBLIC Game GameState TextureManager)