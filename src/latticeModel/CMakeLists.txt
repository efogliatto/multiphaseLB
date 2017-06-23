#------------------ Generacion de bibliotecas ------------------#
 
# LBMmodel library
add_library(latticemodel SHARED 
  latticeVelocities.c
  latticeWeights.c
  latticeReverseDir.c
  MRTMatrix.c
  MRTInvMatrix.c
  D2Q9/D2Q9_Vel.c
  D2Q9/D2Q9_omega.c
  D2Q9/D2Q9_Reverse.c
  D2Q9/D2Q9_MRT.c
  D2Q9/D2Q9_MRTInv.c
  )