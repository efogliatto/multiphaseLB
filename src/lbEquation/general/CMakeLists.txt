#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library.
add_library(generallbe SHARED
  equilibrium.c
  collision.c
  lbstream.c
  macroDensity.c
  macroVelocity.c
  macroTemperature.c
  updateBoundaries.c
  boundary/bounceBack.c
  boundary/fixedT.c
  # updateBoundaryElements.c
  # updateLambda.c
  # updateTau.c
  )