add_library(Lair)

target_link_libraries(Lair PUBLIC Core)

target_include_directories(Lair PUBLIC include)

target_sources(Lair PRIVATE source/lair.cpp)