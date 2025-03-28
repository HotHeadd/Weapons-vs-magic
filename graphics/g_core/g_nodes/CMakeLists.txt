add_library(GNodes)

target_include_directories(GNodes PUBLIC include)

target_sources(GNodes PRIVATE source/g_nodes.cpp)

target_link_libraries(GNodes PUBLIC Core)