#------------------ Generacion de bibliotecas ------------------#
 
# LBMmodel library
add_library(latticemodel SHARED 
  latticeVelocities.c
  latticeWeights.c
  latticeReverseDir.c
  latticeQ.c
  MRTMatrix.c
  MRTInvMatrix.c
  ppWeights.c
  cs2.c
  D2Q9/D2Q9_Vel.c
  D2Q9/D2Q9_omega.c
  D2Q9/D2Q9_Reverse.c
  D2Q9/D2Q9_MRT.c
  D2Q9/D2Q9_MRTInv.c
  D2Q9/D2Q9_ppw.c
  D2Q9/D2Q9_cs2.c
  setLatticeInfo.c
  )