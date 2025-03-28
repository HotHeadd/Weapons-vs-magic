add_library(EnemyFactory)

target_include_directories(EnemyFactory PUBLIC include)

target_sources(EnemyFactory PRIVATE source/enemy_factory.cpp)

target_link_libraries(EnemyFactory PUBLIC Core)