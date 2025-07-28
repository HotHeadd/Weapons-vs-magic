BUILD_DIR = build
BUILD_TEST_DIR = buildtests

TARGET = run

MAKEFLAGS += --no-print-directory

.PHONY : build run runsec setup_test_dirs timetest

final: ${TARGET}

run: build
	./bin/run

runsec: build
	valgrind ./${BUILD_DIR}/run

build:
	mkdir -p ${BUILD_DIR}
	cmake -B${BUILD_DIR} -S.
	cmake --build ${BUILD_DIR}

coverage:
	cmake --build ${BUILD_TEST_DIR} --target coverage


timetest:
	mkdir -p build_timetest
	cmake -Bbuild_timetest -Stimetest
	cmake --build build_timetest
	./bin/timetest

# --verbose для полного вывода тестов
test_layout: setup_test_dirs
	cmake --build ${BUILD_TEST_DIR} --target layout_tests
	ctest --test-dir ${BUILD_TEST_DIR} -R layout --output-on-failure 

test_matrix: setup_test_dirs
	cmake --build ${BUILD_TEST_DIR} --target matrix_tests
	ctest --test-dir ${BUILD_TEST_DIR} -R matrix --output-on-failure 

test_entities_noupdate : setup_test_dirs
	cmake --build ${BUILD_TEST_DIR} --target entities_noupdate_test
	ctest --test-dir ${BUILD_TEST_DIR} -R entities_noupdate --output-on-failure 

test_effects : setup_test_dirs
	cmake --build ${BUILD_TEST_DIR} --target effects_test
	ctest --test-dir ${BUILD_TEST_DIR} -R effects --output-on-failure 

test_all_noupdate : setup_test_dirs
	cmake --build ${BUILD_TEST_DIR} --target effects_test --target entities_noupdate_test
	ctest --test-dir ${BUILD_TEST_DIR} -L NoUpdateTests --output-on-failure 



test_entities_update : setup_test_dirs
	cmake --build ${BUILD_TEST_DIR} --target entity_update_tests
	ctest --test-dir ${BUILD_TEST_DIR} -R entity_update --output-on-failure 

test_systems : setup_test_dirs
	cmake --build ${BUILD_TEST_DIR} --target systems_tests
	ctest --test-dir ${BUILD_TEST_DIR} -R systems --output-on-failure 

test_all_systems : setup_test_dirs
	cmake --build ${BUILD_TEST_DIR} --target systems_tests --target entity_update_tests
	ctest --test-dir ${BUILD_TEST_DIR} -L SystemsTests --output-on-failure

test_factories: setup_test_dirs
	cmake --build ${BUILD_TEST_DIR} --target factories_tests
	ctest --test-dir ${BUILD_TEST_DIR} -R factories --output-on-failure 

test_persistence : setup_test_dirs
	cmake --build ${BUILD_TEST_DIR} --target persistence_tests
	ctest --test-dir ${BUILD_TEST_DIR} -R persistence --output-on-failure 

test_game_methods : setup_test_dirs
	cmake --build ${BUILD_TEST_DIR} --target game_methods_tests
	ctest --test-dir ${BUILD_TEST_DIR} -R game_methods --output-on-failure 


test_complete: setup_test_dirs
	cmake --build ${BUILD_TEST_DIR}
	ctest --test-dir ${BUILD_TEST_DIR} --output-on-failure

setup_test_dirs:
	mkdir -p ${BUILD_TEST_DIR}
	mkdir -p ${BUILD_TEST_DIR}/build_source
	cmake -B${BUILD_TEST_DIR} -Stests