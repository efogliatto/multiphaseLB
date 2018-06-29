#------------------ Generacion de bibliotecas ------------------#
 
# Ensight Gold format
add_library(ensight SHARED
  writeMeshToEnsight.c
  # writeScalarToAsciiRaw.c
  # writeArrayToAsciiRaw.c
  # readScalarFromAsciiRaw.c
  # readArrayFromAsciiRaw.c
  )
