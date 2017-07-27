#------------------ Generacion de bibliotecas ------------------#
 
# Energy equation with compression work
add_library(newtempmodel SHARED
  newTempCollision.c
  newTempEquilibrium.c
  newTempTemperature.c
  )