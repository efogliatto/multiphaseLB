#------------------ Unit tests ------------------#

set ( PROJECT_LINK_LIBS libio.so liblatticemodel.so)
link_directories( ~/multiphaseLB/lib )


# Test 1. basic look up functions
add_executable(test1 "test1.c")
target_link_libraries(test1 ${PROJECT_LINK_LIBS})

# Test 2. lattice Model properties
add_executable(test2 "test2.c")
target_link_libraries(test2 ${PROJECT_LINK_LIBS})
