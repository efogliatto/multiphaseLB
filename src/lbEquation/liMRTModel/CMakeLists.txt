#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library. Li model
add_library(limrtmodel SHARED
  liMRTCollision.c
  liMRTForce.c
  liMRTDensity.c
  liMRTPressure.c
  liMRTVelocity.c
  liMRTEquilibrium.c
  liMRTSurfaceTension.c
  readLiMRTConstants.c
  )
