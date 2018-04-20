#------------------ Generacion de bibliotecas ------------------#
 
# Basic boundary conditions library.
add_library(boundary SHARED
  bounceBack/bounceBack.c
  fixedT/fixedT.c
  fixedU/fixedU.c
  # uniformHeatFlux.c
  # fixedEOSp.c
  outflow/outflow.c
  )
