#ifndef VSTRING_H
#define VSTRING_H

/**
 * @file vstring.h
 * @author Ezequiel O. Fogliatto
 * @date 19 Dic 2018
 * @brief Prints to string with dynamic memory allocation
 * Prints to string with dynamic memory allocation. Similar to asprintf, but portable
 * @param strp Pointer to printed string
 * @param fmt Format as sprintf
 * @return Status. Correct if different from zero
 */

unsigned int vstring( char** strp, const char* fmt, ... );

#endif // VSTRING_H
