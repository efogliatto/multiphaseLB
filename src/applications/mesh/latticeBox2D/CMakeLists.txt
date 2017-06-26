#------------------ Lattice Box 2D------------------#

set ( PROJECT_LINK_LIBS libio.so libbasic.so liblatticemodel.so ${MPI_LIBRARIES})
link_directories( ~/multiphaseLB/lib )


# latticeBox2D
add_executable(latticeBox2D "latticeBox2D.c" "periodicX.c" "periodicY.c" "periodicXY.c" "genericBoundary.c")
target_link_libraries(latticeBox2D ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS})