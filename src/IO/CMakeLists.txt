#------------------ Generacion de bibliotecas ------------------#
 
# IO library
add_library(io SHARED
  readBasicMesh.c
  writeBasicMesh.c
  readLatticeMesh.c
  writeLatticeMesh.c
  writeMeshToVTK.c
  writeScalarField.c
  writeVectorField.c
  readVTKInfo.c
  readTimeInfo.c
  readScalarField.c
  readVectorField.c
  readLbeField.c
  createScalarField.c
  createVectorField.c
  createLbeField.c 
  time/timeOptions.c
  time/readDataFormat.c
  )


# Ascii raw format
add_subdirectory (asciiRaw)


# Pvtu raw format
add_subdirectory (pvtu)


# Binary raw format
add_subdirectory (binaryRaw)


# Ensight Gold format
add_subdirectory (ensight)
