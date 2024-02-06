set(safe_malloc_source
    safe_malloc.h
    safe_malloc.c
)

add_library(safe_malloc ${safe_malloc_source})

target_link_libraries(
    safe_malloc
)
# target_include_directories(safe_malloc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
