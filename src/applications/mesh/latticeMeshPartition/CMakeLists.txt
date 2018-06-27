#------------------ Lattice Mesh Partition------------------#

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
  libasciiraw.so
  libbinaryraw.so
  libpvtu.so  
  # libfinitedifference.so
  m
  ${MPI_LIBRARIES})

# link_directories( ~/multiphaseLB/lib )
link_directories( ${CMAKE_SOURCE_DIR}/lib )



# latticeMeshPartition
add_executable(latticeMeshPartition "latticeMeshPartition.c" "standardDecomp.c" "kmetisDecomp.c" "localIndexing.c")
target_link_libraries(latticeMeshPartition ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS})
