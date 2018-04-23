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
  # updateBdElements.c
  # updateBdForce.c
  singleNodeT.c
  heatSource.c
  )
