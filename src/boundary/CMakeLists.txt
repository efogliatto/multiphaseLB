#------------------ Generacion de bibliotecas ------------------#
 
# Basic boundary conditions library.
add_library(boundary SHARED
  bounceBack/bounceBack.c
  fixedT/fixedT.c
  fixedT/readFixedTParam.c
  fixedU/fixedU.c
  fixedU/readFixedUParam.c  
  # uniformHeatFlux.c
  # fixedEOSp.c
  outflow/outflow.c
  )
