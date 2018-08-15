# Multiphase solver
add_subdirectory (multiPhasePP)

# Multiphase solver with fixed models (test)
add_subdirectory (multiPhase3D)


# GPU version of multhiphase solver

if(WITH_CUDA)

  add_subdirectory (multiPhaseGPU)

endif()
