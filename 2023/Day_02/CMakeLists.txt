# Add the source files for the day
add_executable(Day_02 Day_02.c)
add_executable(Day_02_b Day_02_b.c)

# Include the '/include' directory for the targets
target_include_directories(Day_02 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(Day_02_b PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link '/include' libraries to Day_02 and Day_02_b executables
target_link_libraries(Day_02 PRIVATE safe_malloc)
target_link_libraries(Day_02 PRIVATE get_file)
target_link_libraries(Day_02_b PRIVATE safe_malloc)
target_link_libraries(Day_02_b PRIVATE get_file)
