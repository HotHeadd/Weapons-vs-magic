file(GLOB FACTORIES_FILES *.cpp)
SET(FACTORIES_LIBS Factories TestCreators)
add_executable(factories_tests ${SOURCE_EXE} ${FACTORIES_FILES})
target_link_libraries(factories_tests PRIVATE ${GTEST_LIBS} ${FACTORIES_LIBS})
add_test(NAME factories COMMAND factories_tests)

set_tests_properties(factories PROPERTIES LABELS "FactoriesTests")