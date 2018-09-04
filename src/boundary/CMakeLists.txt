#------------------ Generacion de bibliotecas ------------------#
 
# Basic boundary conditions library.
add_library(boundary SHARED
  bounceBack/bounceBack.c
  fixedT/fixedT.c
  fixedRandomT/fixedRandomT.c
  fixedRandomT/readFixedRandomTParam.c
  fixedT/readFixedTParam.c
  fixedU/fixedU.c
  fixedU/readFixedUParam.c  
  outflow/outflow.c
  # fixedGradT/fixedGradT.c
  fixedGradT/readFixedGradTParam.c  
  )
