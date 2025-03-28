add_library(Enemy)

target_link_libraries(Enemy PUBLIC Core)

target_include_directories(Enemy PUBLIC include)

target_sources(Enemy PRIVATE source/enemy.cpp)