#------------------ Generacion de bibliotecas ------------------#
 
# Dictionary entries
add_library(dictio SHARED
  openDict.c
  bracedEntry.c
  singleEntry.c
  tokenize.c
  lookUpEntry.c
  )
