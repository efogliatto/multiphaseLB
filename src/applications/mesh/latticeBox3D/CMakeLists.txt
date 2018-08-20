#------------------ Lattice Box 2D------------------#

# set ( PROJECT_LINK_LIBS
#   libio.so
#   libdictio.so
#   libbasic.so
#   liblatticemodel.so
#   libgenerallbe.so
#   libpseudopot.so
#   liblimrtmodel.so
#   libmymrtmodel.so
#   libboundary.so
#   libeos.so
#   libfinitedifference.so
#   libasciiraw.so
#   libbinaryraw.so
#   libpvtu.so
#   libensight.so
#   libd2q9.so
#   libd3q15.so
#   libxumrtmodel.so
#   liblitempmrtmodel.so
#   m
#   ${MPI_LIBRARIES})

link_directories( ${CMAKE_SOURCE_DIR}/lib )




# latticeBox3D

add_executable(latticeBox3D "latticeBox3D.c" "genericBoundary3D.c" "periodicXY3D.c" "periodicXY3DSpot.c" "periodicZ3D.c" "periodicXYZ3D.c" )

target_link_libraries(latticeBox3D ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS})
