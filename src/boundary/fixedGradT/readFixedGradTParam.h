#ifndef READFIXEDGRADTPARAM_H
#define READFIXEDGRADTPARAM_H

#include <fixedGradTParam.h>

/**
 * @file readFixedGradTParam.h
 * @author Ezequiel O. Fogliatto
 * @date 20 Apr 2018
 *
 * Read parameters for fixedGradT boundary type
 *
 * @param fname Field name
 * @param bdname Boundary name
 * @return structure with fixed T parameters
 */

fixedGradTParam readFixedGradTParam( char* fname, char* bdname );

#endif // READFIXEDGRADTPARAM_H
