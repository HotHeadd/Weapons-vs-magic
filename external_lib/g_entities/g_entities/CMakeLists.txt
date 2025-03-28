add_library(GEntities INTERFACE)

add_subdirectory(g_towers)
add_subdirectory(g_enemies)
add_subdirectory(g_traps)

target_link_libraries(GEntities INTERFACE GTower)