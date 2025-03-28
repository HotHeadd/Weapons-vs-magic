add_library(TestCreators)

target_include_directories(TestCreators PUBLIC include)

target_sources(TestCreators PRIVATE source/creators.cpp)

target_link_libraries(TestCreators PUBLIC Entities)