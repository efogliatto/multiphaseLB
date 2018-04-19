#ifndef LOOKUPSTRINGLIST_H
#define LOOKUPSTRINGLIST_H

#include <dictionary.h>

/**
 * @file lookUpStringList.h
 * @author Ezequiel O. Fogliatto
 * @date 19 Dic 2018
 * Find string list in dictionary, under braced structure
 * @param dname Dictionary name
 * @param ename Entry name (full path)
 * @param entry Pointer for entry return as string array
 * @return Status. Correct if different from zero
 */

unsigned int lookUpStringList( char* dname, char* ename, char*** entry, unsigned int* n );

#endif // LOOKUPSTRINGLIST_H
