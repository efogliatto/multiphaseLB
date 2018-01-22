#------------------ Generacion de bibliotecas ------------------#
 
# Finite difference differential operations
add_library(finitedifference SHARED 
  scalarGradient.c
  invScalarGradient.c
  vectorDivergence.c
  )
