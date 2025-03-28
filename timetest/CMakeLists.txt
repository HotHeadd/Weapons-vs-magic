cmake_minimum_required(VERSION 3.16)
project(time_counter)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_EXE timetest.cpp time_creators/time_creators.cpp)

add_subdirectory(../source build_source)
add_subdirectory(../external_lib/g_entities/entities_lib ./build_entities)

add_executable(timetest ${SOURCE_EXE})
target_include_directories(timetest PRIVATE time_creators)
target_link_libraries(timetest Game Entities)
set_target_properties(timetest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)