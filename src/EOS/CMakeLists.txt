#------------------ Generacion de bibliotecas ------------------#
 
# EOS library
add_library(eos SHARED
  readEOSInfo.c
  p_eos.c
  # T_eos.c
  # rhoFromEOS.c
  )
