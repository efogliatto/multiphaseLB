#ifndef MRTINVMATRIX_H
#define MRTINVMATRIX_H

#include <D2Q9_MRTInv.h>
#include <latticeInfo.h>

/**
 * @file MRTMatrix.h
 * @author Ezequiel O. Fogliatto
 * @date 17 Apr 2018
 * @brief Inverse of MRT transformation matrix
 */


/**
 * Inverse of MRT transformation matrix (standard)
 * @return \f$ \mathbf{M}^{-1} \f$
 */

double** MRTInvMatrix( DdQq model );

#endif // MRTINVMATRIX_H
