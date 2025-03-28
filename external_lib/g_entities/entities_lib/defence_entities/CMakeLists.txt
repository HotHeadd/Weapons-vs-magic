add_library(DefenceEntities INTERFACE)

add_subdirectory(towers)
add_subdirectory(traps)

target_link_libraries(DefenceEntities INTERFACE Towers Traps)