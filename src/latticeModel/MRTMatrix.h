#ifndef MRTMATRIX_H
#define MRTMATRIX_H

#include <D2Q9_MRT.h>
#include <latticeInfo.h>

/**
 * @file MRTMatrix.h
 * @author Ezequiel O. Fogliatto
 * @date 17 Apr 2018
 * @brief MRT transformation matrix
 */


/**
 * MRT transformation matrix (standard)
 * @return M
 */

scalar** MRTMatrix( DdQq model );

#endif // MRTMATRIX_H
