# https://stackoverflow.com/questions/63992429/cmakelists-include-header-file-from-subdirectories

add_library(safe_malloc
    source/safe_malloc.c
    headers/safe_malloc.h
)

target_sources(safe_malloc
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/source/safe_malloc.c
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/headers/safe_malloc.h
  )

target_include_directories(safe_malloc
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source
)
