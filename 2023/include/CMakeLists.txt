# Add source files
add_library(safe_malloc safe_malloc.c)

# Include the current directory as a public include directory
target_include_directories(safe_malloc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
