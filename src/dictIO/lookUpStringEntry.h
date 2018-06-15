#ifndef LOOKUPSTRINGENTRY_H
#define LOOKUPSTRINGENTRY_H

/**
 * @file lookUpStringEntry.h
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

uint lookUpStringEntry( char* dname, char* ename, char** entry, const char* df );

#endif // LOOKUPSTRINGENTRY_H
