#ifndef LOOKUPINTEGERENTRY_H
#define LOOKUPINTEGERENTRY_H

/**
 * @file lookUpIntegerEntry.h
 * @author Ezequiel O. Fogliatto
 * @date 18 Dic 2018
 * @brief Find integer entry in dictionary
 * @param dname Dictionary name
 * @param ename Entry name
 * @param df Default value if entry is not found
 * @param entry Pointer for entry
 * @return Status. Correct if different from zero
 */

#include <dataTypes.h>

uint lookUpIntegerEntry( char* dname, char* ename, const int df, int* entry );

#endif // LOOKUPINTEGERENTRY_H
