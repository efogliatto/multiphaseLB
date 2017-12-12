#------------------ Generacion de bibliotecas ------------------#
 
# Basic library. Simple operations
add_library(basic SHARED 
  matrixDoubleAlloc.c
  matrixIntAlloc.c
  matVecMult.c
  syncPdfField.c
  syncVectorField.c
  syncScalarField.c
  vectorMag2.c
  )
