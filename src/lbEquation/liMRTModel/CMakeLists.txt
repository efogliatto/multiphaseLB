#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library. Li model
add_library(limrtmodel SHARED
  liMRTCollision.c
  liMRTForce.c  
  )