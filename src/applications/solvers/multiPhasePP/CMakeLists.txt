#------------------ Pseudopotential Solver with Heat Transfer ------------------#

set ( PROJECT_LINK_LIBS libio.so libbasic.so liblatticemodel.so libgenerallbe.so libpseudopot.so liblimrtmodel.so liblisrtmodel.so liblitempmodel.so ${MPI_LIBRARIES})
link_directories( ~/multiphaseLB/lib )


# multiPhasePP
add_executable( multiPhasePP "multiPhasePP.c" )
target_link_libraries(multiPhasePP ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS} ${MPI_LIBRARIES} -lm)
