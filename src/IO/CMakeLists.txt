#------------------ Generacion de bibliotecas ------------------#
 
# IO library
add_library(io SHARED
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
  # writeMainPvd.c
  readTimeInfo.c
  readScalarField.c
  readVectorField.c
  readLbeField.c
  createScalarField.c
  createVectorField.c
  createLbeField.c 
  time/timeOptions.c
  )


# Ascii raw format
add_subdirectory (asciiRaw)


# Pvtu raw format
add_subdirectory (pvtu)
