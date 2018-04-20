#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library. Li model
add_library(limrtmodel SHARED
  liMRTCollision.c
  liMRTForce.c
  liMRTDensity.c
  liMRTVelocity.c
  liMRTEquilibrium.c
  readLiMRTConstants.c
  )
