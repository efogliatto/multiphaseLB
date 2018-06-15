#ifndef PPWEIGHTS_H
#define PPWEIGHTS_H

#include <D2Q9_ppw.h>
#include <latticeInfo.h>

/**
 * @file ppWeights.h
 * @author Ezequiel O. Fogliatto
 * @date 17 Apr 2018
 * @brief Pseudopotential weights
 */


/**
 * Weights for pseudopotential interaction force
 * @return Array of weights \f$ w_i \f$
 */

scalar* ppWeights( DdQq model );

#endif // PPWEIGHTS_H
