add_library(Enemies INTERFACE)

add_subdirectory(enemy)
add_subdirectory(healing_enemy)
add_subdirectory(shooting_enemy)

target_link_libraries(Enemies INTERFACE Enemy HealingEnemy ShootingEnemy)