cmake_minimum_required(VERSION 3.6)
project(linear_sequence_test)

set(PROJECT_NAME linear_sequence_test)

add_subdirectory(lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(TEST_FILES
    src/main.cpp
    src/base_tests.cpp
        src/iterator_tests.cpp
)

add_executable(${PROJECT_NAME} ${TEST_FILES})
target_link_libraries(${PROJECT_NAME} linear_sequence_lib CppUTest)

target_include_directories(${PROJECT_NAME} PUBLIC lib)

