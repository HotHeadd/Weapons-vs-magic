add_library(Tower)

target_link_libraries(Tower PUBLIC Core)

target_include_directories(Tower PUBLIC include)

target_sources(Tower PRIVATE source/tower.cpp)