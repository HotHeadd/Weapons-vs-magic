add_library(EffectFactory)

target_include_directories(EffectFactory PUBLIC include)

target_sources(EffectFactory PRIVATE source/effect_factory.cpp)

target_link_libraries(EffectFactory PUBLIC Core)