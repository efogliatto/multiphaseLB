#------------------ Generacion de bibliotecas ------------------#
 
# Pvtu format
add_library(pvtu SHARED
  writeScalarToPvtu.c
  writeArrayToPvtu.c
  readScalarFromPvtu.c
  readArrayFromPvtu.c
  writeMainPvd.c
  writeMeshToPvtu.c
  writePvtuExtra.c
  )
