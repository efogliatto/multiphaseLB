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
  readVTKInfo.c
  writeVTKExtra.c
  writeMainPvd.c
  readTimeInfo.c
  readScalarField.c
  readVectorField.c
  readLbeField.c
  fileSearch/tokenize.c
  fileSearch/entryList.c
  fileSearch/subEntryList.c
  fileSearch/singleEntryList.c
  fileSearch/lookUpEntry.c
  fileSearch/lookUpDouble.c
  fileSearch/lookUpVector.c
  fileSearch/lookUpString.c
  time/timeOptions.c
  basicInfo/readEOSInfo.c
  )
