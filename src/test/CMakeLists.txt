#------------------ Unit tests ------------------#

set ( PROJECT_LINK_LIBS libio.so )
link_directories( ~/multiphaseLB/lib )


# Test 1. basic look up functions
add_executable(test1 "test1.c")
target_link_libraries(test1 ${PROJECT_LINK_LIBS})
