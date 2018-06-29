#------------------ Generacion de bibliotecas ------------------#
 
# Ensight Gold format
add_library(ensight SHARED
  writeMeshToEnsight.c
  writeScalarToEnsight.c
  writeVectorToEnsight.c
  writeLbeFieldToEnsight.c
  readScalarFromEnsight.c
  timeToIndex.c
  readVectorFromEnsight.c
  readLbeFieldFromEnsight.c
  updateCaseFile.c
  )
