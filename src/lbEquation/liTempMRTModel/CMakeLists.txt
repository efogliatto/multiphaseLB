#------------------ Generacion de bibliotecas ------------------#
 
# Basic lattice-Boltzmann Equation library. Li MRT model for energy equation
add_library(litempmrtmodel SHARED
  liTempMRTCollision.c
  liTempMRTTemperature.c
  liTempMRTEquilibrium.c
  liTempMRTSource.c
  liTempMRTEquilibriumMS.c
  readLiTempMRTConstants.c
  )
