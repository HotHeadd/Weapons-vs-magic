add_library(Layout STATIC source/layout.cpp)

add_subdirectory(matrix)

target_include_directories(Layout PUBLIC include)
target_sources(Layout PRIVATE source/layout.cpp)

target_link_libraries(Layout PUBLIC Matrix Interfaces)