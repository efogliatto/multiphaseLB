#------------------ Generacion de bibliotecas ------------------#
 
# Pseudo - potential basics
add_library(pseudopot SHARED
  # p_eos.c
  # T_eos.c
  potential.c
  interactionForce.c
  totalForce.c
  interForce.c
  # rhoFromEOS.c
  )
