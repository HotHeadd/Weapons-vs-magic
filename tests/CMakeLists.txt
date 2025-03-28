cmake_minimum_required(VERSION 3.16)
project(wvm_tests)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_EXE ${CMAKE_CURRENT_SOURCE_DIR}/run_tests.cpp)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -g")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} --coverage -g")

SET(GTEST_LIBS gtest gtest_main gmock gmock_main)

add_subdirectory(../source ./build_source)
add_subdirectory(../external_lib/g_entities/entities_lib ./build_entities)


add_subdirectory(test_layout)
add_subdirectory(test_entities)
add_subdirectory(test_systems)
add_subdirectory(test_factories)
add_subdirectory(utility)

add_custom_target(coverage
    COMMAND lcov --capture --directory . --output-file coverage.info
    COMMAND lcov --remove coverage.info '/usr/*' '*/tests/*' --output-file coverage_filtered.info
    COMMAND genhtml coverage_filtered.info --output-directory ../coverage_report --title "Test Coverage Report"
)