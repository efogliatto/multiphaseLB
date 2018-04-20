#ifndef READFIXEDTPARAM_H
#define READFIXEDTPARAM_H

#include <fixedTParam.h>

/**
 * @file readFixedTParam.h
 * @author Ezequiel O. Fogliatto
 * @date 20 Apr 2018
 *
 * Read parameters for fixedT boundary type
 *
 * @param fname Field name
 * @param bdname Boundary name
 * @return structure with fixed T parameters
 */

fixedTParam readFixedTParam( char* fname, char* bdname );

#endif // READFIXEDTPARAM_H
