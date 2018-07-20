#------------------ Lattice Box 2D------------------#

set ( PROJECT_LINK_LIBS
  libio.so
  libdictio.so
  libbasic.so
  liblatticemodel.so
  libgenerallbe.so
  libpseudopot.so
  liblimrtmodel.so
  libmymrtmodel.so
  libboundary.so
  libeos.so
  libfinitedifference.so
  libasciiraw.so
  libbinaryraw.so
  libpvtu.so
  libensight.so
  libd2q9.so
  libd3q15.so
  libxumrtmodel.so
  m
  ${MPI_LIBRARIES})

link_directories( ${CMAKE_SOURCE_DIR}/lib )


# latticeBox2D
add_executable(latticeBox2D "latticeBox2D.c" "genericBoundary.c" "periodicX.c" "periodicY.c" "periodicXY.c" )
target_link_libraries(latticeBox2D ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS})
