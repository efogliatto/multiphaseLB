#------------------ Generacion de bibliotecas ------------------#
 
# Dictionary entries
add_library(dictio SHARED
  openDict.c
  bracedEntry.c
  singleEntry.c
  tokenize.c
  lookUpEntry.c
  lookUpStringEntry.c
  lookUpScalarEntry.c
  lookUpIntegerEntry.c
  lookUpVectorEntry.c
  lookUpStringList.c
  isBracedEntryDefined.c
  )
