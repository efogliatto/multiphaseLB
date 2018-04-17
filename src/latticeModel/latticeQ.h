#ifndef LATTICEQ_H
#define LATTICEQ_H

#include <latticeInfo.h>

/**
 * @file latticeQ.h
 * @author Ezequiel O. Fogliatto
 * @date 17 Apr 2018
 * @brief Lattice velocity model
 */


/**
 * @brief Lattice velocity model
 *
 * Lattice velocity model
 * @return Total number of lattice velocities (q from DdQq)
 */

unsigned int latticeQ( DdQq model );

#endif // LATTICEQ_H
