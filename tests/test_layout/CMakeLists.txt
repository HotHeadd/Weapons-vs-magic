file(GLOB MATRIX_FILES test_matrix/*.cpp)
SET(MATRIX_LIBS Matrix)
add_executable(matrix_tests ${SOURCE_EXE} ${MATRIX_FILES})
target_link_libraries(matrix_tests PRIVATE ${GTEST_LIBS} ${MATRIX_LIBS})
add_test(NAME matrix COMMAND matrix_tests)

file(GLOB LAYOUT_FILES test_layout/*.cpp)
SET(LAYOUT_LIBS Layout)
add_executable(layout_tests ${SOURCE_EXE} ${LAYOUT_FILES})
target_link_libraries(layout_tests PRIVATE ${GTEST_LIBS} ${LAYOUT_LIBS})
add_test(NAME layout COMMAND layout_tests)

set_tests_properties(matrix PROPERTIES LABELS "LayoutTests")
set_tests_properties(layout PROPERTIES LABELS "LayoutTests")