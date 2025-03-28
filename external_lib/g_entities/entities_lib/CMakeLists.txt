add_library(Entities INTERFACE)

add_subdirectory(effect_types)
target_link_libraries(Entities INTERFACE Effects)

add_subdirectory(defence_entities)
target_link_libraries(Entities INTERFACE DefenceEntities)

add_subdirectory(enemy_entities)
target_link_libraries(Entities INTERFACE Enemies)