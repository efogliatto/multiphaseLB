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
  libxumrtmodel.so
  libboundary.so
  libeos.so
  libfinitedifference.so
  libpvtu.so
  libasciiraw.so
  libbinaryraw.so
  libensight.so
  libd2q9.so
  libd3q15.so
  m
  ${MPI_LIBRARIES}
  )


# link_directories( ~/multiphaseLB/lib )
link_directories( ${CMAKE_SOURCE_DIR}/lib )


# Test 1. basic look up functions
add_executable(test1 "test1.c")
target_link_libraries(test1 ${PROJECT_LINK_LIBS}  ${PROJECT_LINK_LIBS} ${MPI_LIBRARIES} -lm)

# # Test 2. Performance
# add_executable(test2 "test2.c")
# target_link_libraries(test2 ${PROJECT_LINK_LIBS}  ${PROJECT_LINK_LIBS} ${MPI_LIBRARIES} -lm)

# Test 3. Ensight format
add_executable(test3 "test3.c")
target_link_libraries(test3 ${PROJECT_LINK_LIBS}  ${PROJECT_LINK_LIBS} ${MPI_LIBRARIES} -lm)
