add_library(SystemTypes)

target_include_directories(SystemTypes PUBLIC include)

target_sources(SystemTypes PRIVATE source/defence_system.cpp
                               source/effect_system.cpp
                               source/enemy_system.cpp
                               source/lair_system.cpp)

target_link_libraries(SystemTypes PUBLIC Core)