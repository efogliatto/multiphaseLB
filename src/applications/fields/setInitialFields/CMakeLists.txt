#------------------ Initial fields------------------#

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
  libxumrtmodel.so
  libboundary.so
  libeos.so
  libpvtu.so
  libasciiraw.so
  libbinaryraw.so
  libensight.so
  libd2q9.so
  libd3q15.so
  # libfinitedifference.so
  m
  ${MPI_LIBRARIES})

# link_directories( ~/multiphaseLB/lib )
link_directories( ${CMAKE_SOURCE_DIR}/lib )


# setInitialFields
add_executable(setInitialFields "setInitialFields.c"
  "uniformScalarField.c"
  "boxBoundedScalarField.c"
  "randomScalarField.c"
  "sphereBoundedScalarField.c"
  "fixedGradientScalarField.c"
  "tgProfileScalarField.c"  )

target_link_libraries(setInitialFields ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS})
