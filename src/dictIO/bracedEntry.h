#ifndef BRACEDENTRY_H
#define BRACEDENTRY_H

/**
 * @file bracedEntry.h
 * @author Ezequiel O. Fogliatto
 * @date 18 Dic 2018
 * @brief Find braced limited entry
 */

/**
 * @brief Find braced limited entry
 * @param ename Entry name
 * @param content String where search occurs
 * @param entry Pointer to entry. If ename is found, entry is reallocated.
 * @return Status. Correct if different from zero
 */

unsigned int bracedEntry( char* ename, char* content, char** entry );

#endif // BRACEDENTRY_H
