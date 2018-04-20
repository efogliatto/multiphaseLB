#------------------ Generacion de bibliotecas ------------------#
 
# Basic boundary conditions library.
add_library(boundary SHARED
  bounceBack.c
  # fixedT.c
  # fixedU.c
  # uniformHeatFlux.c
  # fixedEOSp.c
  # outflow.c
  )
