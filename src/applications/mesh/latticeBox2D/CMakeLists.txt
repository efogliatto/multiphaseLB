#------------------ Lattice Box 2D------------------#

set ( PROJECT_LINK_LIBS
  libio.so
  libdictio.so
  libbasic.so
  liblatticemodel.so
  # libgenerallbe.so
  # libpseudopot.so
  libpseudopot.so
  liblimrtmodel.so
  libmymrtmodel.so
  libboundary.so
  libeos.so
  # libfinitedifference.so
  ${MPI_LIBRARIES})
link_directories( ~/multiphaseLB/lib )


# latticeBox2D
add_executable(latticeBox2D "latticeBox2D.c" "genericBoundary.c" "periodicX.c" "periodicY.c" "periodicXY.c" )
target_link_libraries(latticeBox2D ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS})
