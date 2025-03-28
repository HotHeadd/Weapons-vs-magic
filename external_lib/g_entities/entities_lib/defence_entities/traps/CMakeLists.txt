add_library(Traps INTERFACE)

add_subdirectory(trap)
add_subdirectory(magic_trap)

target_link_libraries(Traps INTERFACE Trap)
target_link_libraries(Traps INTERFACE MagicTrap)