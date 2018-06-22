#ifndef READFIXEDRANDOMTPARAM_H
#define READFIXEDRANDOMTPARAM_H

#include <fixedRandomTParam.h>

/**
 * @file readFixedRandomTParam.h
 * @author Ezequiel O. Fogliatto
 * @date 20 Apr 2018
 *
 * Read parameters for fixedRandomT boundary type
 *
 * @param fname Field name
 * @param bdname Boundary name
 * @return structure with fixed T parameters
 */

fixedRandomTParam readFixedRandomTParam( char* fname, char* bdname );

#endif // READFIXEDRANDOMTPARAM_H
