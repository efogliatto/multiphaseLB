#------------------ Unit tests ------------------#

set ( PROJECT_LINK_LIBS
  dictio.so
  # libio.so
  libbasic.so
  # liblatticemodel.so
  # libgenerallbe.so
  # libpseudopot.so
  # liblimrtmodel.so
  # liblisrtmodel.so
  # liblitempmodel.so
  # libmymrtmodel.so
  # libfinitedifference.so
  ${MPI_LIBRARIES}
  )


link_directories( ~/multiphaseLB/lib )


# Test 1. basic look up functions
add_executable(test1 "test1.c")
target_link_libraries(test1 ${PROJECT_LINK_LIBS})

# Test 2. 
add_executable(test2 "test2.c")
target_link_libraries(test2 ${PROJECT_LINK_LIBS})

# # Test 3. mpi sync
# add_executable(test3 "test3.c")
# target_link_libraries(test3 ${PROJECT_LINK_LIBS})

# # Test 4. Finite difference operators
# add_executable(test4 "test4.c")
# target_link_libraries(test4 ${PROJECT_LINK_LIBS})
