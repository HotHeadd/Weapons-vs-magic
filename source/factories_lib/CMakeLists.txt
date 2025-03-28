add_library(Factories INTERFACE)

add_subdirectory(effect_factory)
add_subdirectory(tower_factory)
add_subdirectory(trap_factory)
add_subdirectory(enemy_factory)
add_subdirectory(factory_manager)


target_link_libraries(Factories INTERFACE FactoryManager)