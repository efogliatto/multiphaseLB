#------------------ Lattice Mesh Partition------------------#

set ( PROJECT_LINK_LIBS libio.so libbasic.so liblatticemodel.so ${MPI_LIBRARIES})
link_directories( ~/multiphaseLB/lib )

# latticeMeshPartition
add_executable(latticeMeshPartition "latticeMeshPartition.c" "standardDecomp.c" "localIndexing.c")
target_link_libraries(latticeMeshPartition ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS})