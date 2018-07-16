#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library. Xu model
add_library(xumrtmodel SHARED
  xuMRTCollision.c
  xuMRTForce.c
  xuMRTDensity.c
  xuMRTPressure.c
  xuMRTVelocity.c
  xuMRTEquilibrium.c
  xuMRTEquilibriumMS.c
  xuMRTSurfaceTension.c
  readXuMRTConstants.c
  )
