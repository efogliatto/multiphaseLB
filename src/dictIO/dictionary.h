#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @file dictionary.h
 * @author Ezequiel O. Fogliatto
 * @date 18 Dic 2018
 * @brief Dictionary structure
 */


typedef struct {

    /** Dictionary content as single string */
    char *content;

    /** File version */
    unsigned int version;

} dictionary;

#endif // DICTIONARY_H
