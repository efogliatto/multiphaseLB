#ifndef LATTICEREVERSEDIR_H
#define LATTICEREVERSEDIR_H

#include <D2Q9_Reverse.h>
#include <latticeInfo.h>

/**
 * @file latticeReverseDir.h
 * @author Ezequiel O. Fogliatto
 * @date 17 Apr 2018
 * @brief Lattice reverse directions
 */


/**
 * Lattice reverse directions
 * @return Array of lattice reverse directions as integer indices. E.g., for D2Q9, lrd[1] = 3
 */


int* latticeReverseDir( DdQq model );

#endif // LATTICEREVERSEDIR_H
