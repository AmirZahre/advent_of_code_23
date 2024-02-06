project(AdventOfCode2023Day02)

# Add the source files for the day
add_executable(${PROJECT_NAME} Day_02.c)

# Include directories for the project
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/../../include)

# # Specify the library path
# link_directories(${PROJECT_SOURCE_DIR}/../../build/include)

# Link any libraries needed from the include folder
target_link_libraries(${PROJECT_NAME} PRIVATE safe_malloc)
