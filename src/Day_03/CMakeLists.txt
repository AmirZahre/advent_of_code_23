
add_executable(Day_03 Day_03.c)
include_directories(${CMAKE_SOURCE_DIR}/lib) # include files from lib (library)

target_link_libraries(Day_03 safe_malloc)
