#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library. Li model
add_library(litempmodel SHARED
  liTempCollision.c
  liTempEquilibrium.c
  liTempTemperature.c
  )