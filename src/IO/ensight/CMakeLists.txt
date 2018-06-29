#------------------ Generacion de bibliotecas ------------------#
 
# Ensight Gold format
add_library(ensight SHARED
  writeMeshToEnsight.c
  writeScalarToEnsight.c
  # writeArrayToEnsight.c
  # readScalarFromEnsight.c
  # readArrayFromEnsight.c
  )
