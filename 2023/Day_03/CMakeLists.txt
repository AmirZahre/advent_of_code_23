# project(AdventOfCode2023Day02)

# Add the source files for the day
add_executable(Day_03 Day_03.c)


# Include the 'include' directory for the target
target_include_directories(Day_03 PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link 'mylib' library to Day_03 executable
target_link_libraries(Day_03 PRIVATE safe_malloc)
