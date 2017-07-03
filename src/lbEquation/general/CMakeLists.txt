#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library.
add_library(generallbe SHARED
  equilibrium.c
  collision.c
  # macroDensity.c
  # macroVelocity.c
  # macroTemperature.c
  # updateBoundaries.c
  # updateBoundaryElements.c
  # updateLambda.c
  # updateTau.c
  )