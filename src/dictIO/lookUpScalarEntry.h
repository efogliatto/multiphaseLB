#ifndef LOOKUPSCALARENTRY_H
#define LOOKUPSCALARENTRY_H

/**
 * @file lookUpScalarEntry.h
 * @author Ezequiel O. Fogliatto
 * @date 18 Dic 2018
 * @brief Find scalar entry in dictionary
 * @param dname Dictionary name
 * @param ename Entry name (full path)
 * @param df Default value if entry is not found
 * @param entry Pointer for entry
 * @return Status. Correct if different from zero
 */

unsigned int lookUpScalarEntry( char* dname, char* ename, const double df, double* entry );

#endif // LOOKUPSCALARENTRY_H
