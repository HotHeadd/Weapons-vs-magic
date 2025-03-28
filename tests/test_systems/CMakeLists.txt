file(GLOB ENTITY_UPD_FILES test_entities_updates/*.cpp)
SET(ENTITY_UPD_LIBS Systems Lair Entities Factories TestCreators)
add_executable(entity_update_tests ${SOURCE_EXE} ${ENTITY_UPD_FILES})
target_link_libraries(entity_update_tests ${GTEST_LIBS} ${ENTITY_UPD_LIBS})
add_test(NAME entity_update COMMAND entity_update_tests)


file(GLOB SYSTEM_FILES test_system/*.cpp)
SET(SYSTEM_LIBS Systems)
add_executable(systems_tests ${SOURCE_EXE} ${SYSTEM_FILES})
target_link_libraries(systems_tests ${GTEST_LIBS} ${SYSTEM_LIBS})
add_test(NAME systems COMMAND systems_tests)

set_tests_properties(systems PROPERTIES LABELS "SystemsTests")
set_tests_properties(entity_update PROPERTIES LABELS "SystemsTests")