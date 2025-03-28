add_library(Trap)

target_include_directories(Trap PUBLIC include)
target_sources(Trap PRIVATE source/trap.cpp)

target_link_libraries(Trap PUBLIC Core)