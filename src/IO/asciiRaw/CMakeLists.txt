#------------------ Generacion de bibliotecas ------------------#
 
# Ascii Raw format
add_library(asciiraw SHARED
  writeScalarToAsciiRaw.c
  writeArrayToAsciiRaw.c
  readScalarFromAsciiRaw.c
  readArrayFromAsciiRaw.c
  )
