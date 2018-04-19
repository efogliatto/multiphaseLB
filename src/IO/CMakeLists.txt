#------------------ Generacion de bibliotecas ------------------#
 
# IO library
add_library(io SHARED
  # openFile.c
  readBasicMesh.c
  # writeBasicMesh.c
  readLatticeMesh.c
  # writeLatticeMesh.c
  # writeMeshToVTK.c
  # writeScalarToVTK.c
  # writeVectorToVTK.c
  # writePdfToVTK.c
  # readVTKInfo.c
  # writeVTKExtra.c
  # writeMainPvd.c
  readTimeInfo.c
  readScalarField.c
  readVectorField.c
  readLbeField.c
  # createScalarField.c
  # createVectorField.c
  # createLbeField.c 
  # time/timeOptions.c
  # basicInfo/readEOSInfo.c
  )
