#------------------ Generacion de bibliotecas ------------------#
 
# IO library
add_library(io SHARED
  lookUpDoubleEntry.c
  lookUpStringEntry.c
  openFile.c
  readBasicMesh.c
  writeBasicMesh.c
  readLatticeMesh.c
  writeLatticeMesh.c
  writeMeshToVTK.c
  writeScalarToVTK.c
  writeVectorToVTK.c
  writePdfToVTK.c
  writeVTKExtra.c
  writeMainPvd.c
  )
