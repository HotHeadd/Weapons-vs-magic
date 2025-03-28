add_library(MagicTrap)

target_include_directories(MagicTrap PUBLIC include)

target_sources(MagicTrap PRIVATE source/magic_trap.cpp)

target_link_libraries(MagicTrap PUBLIC Core Trap)