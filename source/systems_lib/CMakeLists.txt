add_library(Systems INTERFACE)

add_subdirectory(system_manager)
add_subdirectory(system_types)

target_link_libraries(Systems INTERFACE SystemManager)
target_link_libraries(Systems INTERFACE SystemTypes)
