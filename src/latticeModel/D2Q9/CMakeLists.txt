#------------------ Generacion de bibliotecas ------------------#
 
# LBMmodel library
add_library(d2q9 SHARED 
  D2Q9_Vel.c
  D2Q9_omega.c
  D2Q9_Reverse.c
  D2Q9_MRT.c
  D2Q9_MRTInv.c
  D2Q9_ppw.c
  D2Q9_cs2.c
  )
