set(SOURCES source/poisoning.cpp source/slowdown.cpp source/weakening.cpp)

add_library(Effects)

target_link_libraries(Effects PUBLIC Core)

target_include_directories(Effects PUBLIC include)

target_sources(Effects PRIVATE ${SOURCES})