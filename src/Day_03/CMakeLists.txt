
include_directories(${CMAKE_SOURCE_DIR}/lib/headers) # include files from lib (library)

add_executable(Day_03 Day_03.c)

target_link_libraries(Day_03 safe_malloc)
