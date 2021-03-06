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

#include <dataTypes.h>

uint lookUpScalarEntry( char* dname, char* ename, const scalar df, scalar* entry );

#endif // LOOKUPSCALARENTRY_H
