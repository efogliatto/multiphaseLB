#------------------ Generacion de bibliotecas ------------------#
 
# LBMmodel library
add_library(d3q15 SHARED 
  D3Q15_Vel.c
  D3Q15_omega.c
  # d3q15_Reverse.c
  D3Q15_MRT.c
  # D3Q15_MRTInv.c
  D3Q15_ppw.c
  D3Q15_cs2.c
  )
