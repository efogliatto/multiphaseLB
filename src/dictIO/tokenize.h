#ifndef TOKENIZE_H
#define TOKENIZE_H

/**
 * @file tokenize.h
 * @author Ezequiel O. Fogliatto
 * @date 18 Dic 2018
 * @brief String spliting into token /
 */

/**
 * @brief String spliting into token /
 * @param src Original string
 * @param dest Pointer to destination array
 * @param n Number of split parts
 * @return Status. Correct if different from zero
 */

unsigned int tokenize( char* src, char ***dest, unsigned int* n );

#endif // TOKENIZE_H
