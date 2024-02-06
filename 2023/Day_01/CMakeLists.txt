# Add the source files for the day
add_executable(Day_01 Day_01.c)

# Include the '/include' directory for the target
target_include_directories(Day_01 PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link '/include' libraries to Day_01 executable
target_link_libraries(Day_01 PRIVATE safe_malloc)
target_link_libraries(Day_01 PRIVATE get_file)
