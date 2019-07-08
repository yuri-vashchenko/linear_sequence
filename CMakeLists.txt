cmake_minimum_required(VERSION 3.6)
project(linear_sequence_test)

set(PROJECT_NAME linear_sequence_test)

add_subdirectory(lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} linear_sequence_lib)
target_include_directories(${PROJECT_NAME} PUBLIC lib)

