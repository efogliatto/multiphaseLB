#------------------ Unit tests ------------------#

set ( PROJECT_LINK_LIBS
  libio.so
  libdictio.so
  libbasic.so
  liblatticemodel.so
  libgenerallbe.so
  libpseudopot.so
  libpseudopot.so
  liblimrtmodel.so
  libmymrtmodel.so
  libboundary.so
  libeos.so
  libfinitedifference.so
  ${MPI_LIBRARIES}
  )


link_directories( ~/multiphaseLB/lib )


# Test 1. basic look up functions
add_executable(test1 "test1.c")
target_link_libraries(test1 ${PROJECT_LINK_LIBS})

# Test 2. Performance
add_executable(test2 "test2.c")
target_link_libraries(test2 ${PROJECT_LINK_LIBS})
