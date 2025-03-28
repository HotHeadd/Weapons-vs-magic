file(GLOB ENTITIES_NOUPD_FILES test_entities_noupdate/*.cpp)
SET(ENTITIES_NOUPD_LIBS Entities Effects EffectFactory)
add_executable(entities_noupdate_test ${SOURCE_EXE} ${ENTITIES_NOUPD_FILES})
target_link_libraries(entities_noupdate_test ${GTEST_LIBS} ${ENTITIES_NOUPD_LIBS})
add_test(NAME entities_noupdate COMMAND entities_noupdate_test)


file(GLOB EFFECTS_FILES test_effects/*.cpp)
SET(EFFECTS_LIBS Enemy Effects EffectFactory)
add_executable(effects_test ${SOURCE_EXE} ${EFFECTS_FILES})
target_link_libraries(effects_test ${GTEST_LIBS} ${EFFECTS_LIBS})
add_test(NAME effects COMMAND effects_test)

set_tests_properties(entities_noupdate PROPERTIES LABELS "NoUpdateTests")
set_tests_properties(effects PROPERTIES LABELS "NoUpdateTests")