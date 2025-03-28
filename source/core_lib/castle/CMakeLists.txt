add_library(Castle)

target_include_directories(Castle PUBLIC include)

target_sources(Castle PRIVATE source/castle.cpp)
target_link_libraries(Castle PUBLIC Interfaces)