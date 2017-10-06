#------------------ Initial fields------------------#

set ( PROJECT_LINK_LIBS libio.so libbasic.so liblatticemodel.so ${MPI_LIBRARIES})
link_directories( ~/multiphaseLB/lib )

# setInitialFields
add_executable(setInitialFields "setInitialFields.c" "uniformScalarField.c" "randomScalarField.c" "boxBoundedScalarField.c" "sphereBoundedScalarField.c" "fixedGradientScalarField.c")
target_link_libraries(setInitialFields ${PROJECT_LINK_LIBS} ${PROJECT_LINK_LIBS})
