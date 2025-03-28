add_library(TrapFactory)

target_include_directories(TrapFactory PUBLIC include)

target_sources(TrapFactory PRIVATE source/trap_factory.cpp)

target_link_libraries(TrapFactory PUBLIC Core)