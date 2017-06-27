#------------------ Generacion de bibliotecas ------------------#
 
# IO library
add_library(io SHARED
  lookUpDoubleEntry.c
  lookUpStringEntry.c
  openFile.c
  readBasicMesh.c
  writeBasicMesh.c
  writeLatticeMesh.c
  )
