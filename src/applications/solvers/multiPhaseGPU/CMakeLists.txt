#------------------ Pseudopotential Solver with Heat Transfer ------------------#

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
  ${MPI_LIBRARIES})

# link_directories( ~/multiphaseLB/lib )
link_directories( ${CMAKE_SOURCE_DIR}/lib )

# multiPhaseGPU
cuda_add_executable( multiPhaseGPU "multiPhaseGPU.cu" "../multiPhasePP/checkMpArgs.c" )

target_link_libraries( multiPhaseGPU ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS} ${MPI_LIBRARIES} -lm)

# target_compile_options( multiPhaseGPU )
