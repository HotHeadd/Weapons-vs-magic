add_library(EffectHolders)

target_include_directories(EffectHolders PUBLIC include)

target_sources(EffectHolders PRIVATE source/effected.cpp
                           source/magic.cpp)

target_link_libraries(EffectHolders PUBLIC Interfaces)
