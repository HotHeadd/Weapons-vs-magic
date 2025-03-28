add_library(GTrap)

target_include_directories(GTrap PUBLIC include)

target_sources(GTrap PRIVATE source/g_trap.cpp)

target_link_libraries(GTrap PUBLIC Trap Renderable GameState TextureManager)