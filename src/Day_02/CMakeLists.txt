
add_executable(Day_02 Day_02.c)
add_executable(Day_02_b Day_02_b.c)

include_directories(${CMAKE_SOURCE_DIR}/lib) # include files from lib (library)

target_link_libraries(Day_02 safe_malloc)
