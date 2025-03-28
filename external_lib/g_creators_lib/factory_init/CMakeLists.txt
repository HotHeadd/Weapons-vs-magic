add_library(InitFactory SHARED)

target_include_directories(InitFactory PUBLIC include)
target_sources(InitFactory PRIVATE source/inits.cpp)

target_link_libraries(InitFactory PUBLIC BaseCreators Core)

set_target_properties(InitFactory PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../../assets/plugins)