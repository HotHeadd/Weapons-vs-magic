add_library(HealingEnemy)

target_link_libraries(HealingEnemy PUBLIC Enemy)

target_include_directories(HealingEnemy PUBLIC include)

target_sources(HealingEnemy PRIVATE source/healing_enemy.cpp)