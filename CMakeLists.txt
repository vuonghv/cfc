cmake_minimum_required (VERSION 3.2.2)
project (poseidon)

set(CMAKE_C_FLAGS "-std=c99")

file(GLOB SOURCES "src/*.c")
add_library(poseidon SHARED ${SOURCES})
add_executable(test_set test/test_set.c)
target_link_libraries(test_set poseidon)
