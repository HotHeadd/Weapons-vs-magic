add_library(SystemManager)

target_include_directories(SystemManager PUBLIC include)

target_sources(SystemManager PRIVATE source/system_manager.cpp)
target_link_libraries(SystemManager PUBLIC Core SystemTypes)
