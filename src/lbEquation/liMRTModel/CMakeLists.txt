#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library. Li model
add_library(limrtmodel SHARED
  liMRTCollision.c  
  # potential.c
  # interactionForce.c
  # totalForce.c
  # liDensity.c
  # # liVelocity.c
  # liMRTForce.c
  # liEquilibrium.c
  # # liCollision.c
  # # pseudoPotCollision.c
  # temperatureCollision.c
  # pseudoPotVelocity.c
  # pseudoPotTemperature.c
  # liSRTCollision.c
  # guoSRTCollision.c  
  # liVelocity_local.c
  # liDensity_local.c
  # liTemperature_local.c
  # lbgkEquilibrium.c
  )