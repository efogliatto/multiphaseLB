#ifndef SINGLEENTRY_H
#define SINGLEENTRY_H

/**
 * @file singleEntry.h
 * @author Ezequiel O. Fogliatto
 * @date 18 Dic 2018
 * @brief Find single entry (; finished) in string
 */

/**
 * Find single entry (; finished) in string. 
 * If @p content and @p *entry are the same pointer (allowed), @p *content is modified.
 * @brief Find single entry (; finished) in string
 * @param ename Entry name
 * @param content String where search occurs
 * @param entry Pointer to entry. If ename is found, entry is reallocated.
 * @return Status. Correct if different from zero
 */

#include <dataTypes.h>

uint singleEntry( char* ename, char* content, char** entry );

#endif // SINGLEENTRY_H
