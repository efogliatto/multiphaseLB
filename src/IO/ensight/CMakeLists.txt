#------------------ Generacion de bibliotecas ------------------#
 
# Ensight Gold format
add_library(ensight SHARED
  writeMeshToEnsight.c
  writeScalarToEnsight.c
  writeVectorToEnsight.c
  # readScalarFromEnsight.c
  # readVectorFromEnsight.c
  )
