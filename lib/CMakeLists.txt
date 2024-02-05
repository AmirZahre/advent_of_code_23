# https://stackoverflow.com/questions/63992429/cmakelists-include-header-file-from-subdirectories

add_library(safe_malloc
headers/safe_malloc.h
source/safe_malloc.c
)

# add_subdirectory("headers")
# add_subdirectory("source")


target_include_directories(safe_malloc 
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source
)