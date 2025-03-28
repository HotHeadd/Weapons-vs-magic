add_library(BaseCreators INTERFACE)

add_library(EffectCreators)
add_library(EnemyCreators)
add_library(TowerCreators)
add_library(TrapCreators)

target_include_directories(EffectCreators PUBLIC include)
target_include_directories(EnemyCreators PUBLIC include)
target_include_directories(TowerCreators PUBLIC include)
target_include_directories(TrapCreators PUBLIC include)

target_sources(EffectCreators PRIVATE source/effect_creators.cpp)
target_sources(EnemyCreators PRIVATE source/enemy_creators.cpp)
target_sources(TowerCreators PRIVATE source/tower_creators.cpp)
target_sources(TrapCreators PRIVATE source/trap_creators.cpp)
 
target_link_libraries(EffectCreators PUBLIC Effects)
target_link_libraries(EnemyCreators PUBLIC GEnemy)
target_link_libraries(TowerCreators PUBLIC GNodes GTower GMagicTower)
target_link_libraries(TrapCreators PUBLIC GNodes GTrap GMagicTrap)

target_link_libraries(BaseCreators INTERFACE EffectCreators EnemyCreators TowerCreators TrapCreators)
