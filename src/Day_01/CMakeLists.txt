# Advent of Code 2023 Day 1
add_executable(Day_01 Day_01.c)

target_link_libraries(Day_01 safe_malloc)

include_directories(${CMAKE_SOURCE_DIR}/lib) # include files from lib (library)