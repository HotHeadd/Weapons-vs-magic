add_library(Core INTERFACE)

add_subdirectory(layout)
add_subdirectory(effect_holders)
add_subdirectory(castle)
add_subdirectory(interfaces)

target_link_libraries(Core INTERFACE Layout Castle EffectHolders)