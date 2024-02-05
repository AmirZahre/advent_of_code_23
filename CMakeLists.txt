# Top-level CMake project file for the 2023 Advent of Code
# Includes sub-projects (one for each day)

cmake_minimum_required(VERSION 3.2.0)
project(AdventofCode2023 LANGUAGES C)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
include(CPack)

add_subdirectory("src")
add_subdirectory("lib")

# file(GLOB SOURCES "src/*/*.c")

# add_executable(${PROJECT_NAME} ${SOURCES})


# target_link_libraries(${PROJECT_NAME} PUBLIC safe_malloc)

# https://stackoverflow.com/questions/13703647/how-to-properly-add-include-directories-with-cmake