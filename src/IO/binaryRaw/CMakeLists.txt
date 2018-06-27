#------------------ Generacion de bibliotecas ------------------#
 
# Binary Raw format
add_library(binaryraw SHARED
  writeScalarToBinaryRaw.c
  writeArrayToBinaryRaw.c
  readScalarFromBinaryRaw.c
  readArrayFromBinaryRaw.c
  )
