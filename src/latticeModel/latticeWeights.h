#ifndef LATTICEWEIGHTS_H
#define LATTICEWEIGHTS_H

#include <D2Q9_omega.h>
#include <latticeInfo.h>

/**
 * @file latticeWeights.h
 * @author Ezequiel O. Fogliatto
 * @date 17 Apr 2018
 * @brief Lattice weights
 */


/**
 * Lattice weights for equilibrium distributions
 * @return Array of lattice weights \f$ \omega_i \f$
 */

double* latticeWeights( DdQq model );

#endif // LATTICEWEIGHTS_H
