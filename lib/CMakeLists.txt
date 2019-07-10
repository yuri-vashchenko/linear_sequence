cmake_minimum_required(VERSION 3.6)
project(linear_sequence_lib)

set(SOURCE_FILES linear_sequence.c linear_sequence.h)
add_library(linear_sequence_lib STATIC ${SOURCE_FILES})
