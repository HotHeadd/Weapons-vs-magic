add_library(ShootingEnemy)

target_link_libraries(ShootingEnemy PUBLIC Enemy)

target_include_directories(ShootingEnemy PUBLIC include)

target_sources(ShootingEnemy PRIVATE source/shooting_enemy.cpp)