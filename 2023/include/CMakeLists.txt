# Add source files
add_library(safe_malloc safe_malloc.c)
add_library(get_file get_file.c)

# Include the current directory as a public include directory
target_include_directories(safe_malloc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(get_file PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

