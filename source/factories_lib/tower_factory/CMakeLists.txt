add_library(TowerFactory)

target_include_directories(TowerFactory PUBLIC include)

target_sources(TowerFactory PRIVATE source/tower_factory.cpp)

target_link_libraries(TowerFactory PUBLIC Core)