#ifndef LOOKUPENTRY_H
#define LOOKUPENTRY_H

#include <dictionary.h>

/**
 * @file lookUpEntry.h
 * @author Ezequiel O. Fogliatto
 * @date 18 Dic 2018
 * @brief Find single entry in dictionary, under braced structure
 * @param dname Dictionary name
 * @param ename Entry name (full path)
 * @param entry Pointer for entry return as string
 * @return Status. Correct if different from zero
 */

uint lookUpEntry( char* dname, char* ename, char** entry );

#endif // LOOKUPENTRY_H
