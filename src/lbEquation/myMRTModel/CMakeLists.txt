#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library. my MRT model for energy equation
add_library(mymrtmodel SHARED
  myMRTCollision.c
  myMRTTemperature.c
  myMRTEquilibrium.c
  myMRTSource.c
  )
