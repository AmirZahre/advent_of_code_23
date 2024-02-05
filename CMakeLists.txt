# Top-level CMake project file for the 2023 Advent of Code
# Includes sub-projects (one for each day)

cmake_minimum_required(VERSION 3.2.0)
project(AdventofCode2023 LANGUAGES C)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
include(CPack)

add_subdirectory("src/Day_01")
add_subdirectory("src/Day_02")
# add_subdirectory("src/Day_03")