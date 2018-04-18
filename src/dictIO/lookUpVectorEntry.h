#ifndef LOOKUPVECTORENTRY_H
#define LOOKUPVECTORENTRY_H

/**
 * @file lookUpVectorEntry.h
 * @author Ezequiel O. Fogliatto
 * @date 18 Dic 2018
 * @brief Find Vector entry in dictionary
 * @param dname Dictionary name
 * @param ename Entry name (full path)
 * @param entry Pointer for entry
 * @param n Vector size
 * @return Status. Correct if different from zero
 */

unsigned int lookUpVectorEntry( char* dname, char* ename, double** entry, unsigned int* n );

#endif // LOOKUPVECTORENTRY_H
