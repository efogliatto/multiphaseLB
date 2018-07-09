#------------------ Generacion de bibliotecas ------------------#
 
# LBMmodel library
add_library(latticemodel SHARED 
  latticeVelocities.c
  latticeWeights.c
  latticeReverseDir.c
  latticeQ.c
  latticeD.c
  MRTMatrix.c
  MRTInvMatrix.c
  ppWeights.c
  cs2.c
  setLatticeInfo.c
  )



# D2Q9
add_subdirectory (D2Q9)


# D3Q15
add_subdirectory (D3Q15)
