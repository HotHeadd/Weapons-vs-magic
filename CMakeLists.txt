cmake_minimum_required(VERSION 3.16)
project(weapon_vs_magic)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_EXE run.cpp)

find_package(SFML COMPONENTS graphics window system REQUIRED)

add_subdirectory(source)
add_subdirectory(graphics)
add_subdirectory(external_lib)

add_executable(run ${SOURCE_EXE})

set_target_properties(run PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

target_link_libraries(run Game RenderManager)