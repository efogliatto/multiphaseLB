#ifndef ISBRACEDENTRYDEFINED_H
#define ISBRACEDENTRYDEFINED_H

/**
 * @file isbracedEntryDefined.h
 * @author Ezequiel O. Fogliatto
 * @date 18 Dic 2018
 * @brief Checks if braced entry is present in dicionary
 */

/**
 * @brief Checks if braced entry is present in dicionary
 * @param dname Dictionary name
 * @param ename String with entry name (full path)
 * @return Status. True if different from zero
 */

unsigned int isBracedEntryDefined( char* dname, char* ename );

#endif // ISBRACEDENTRYDEFINED_H
