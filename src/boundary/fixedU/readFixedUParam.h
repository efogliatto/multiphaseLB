#ifndef READFIXEDUPARAM_H
#define READFIXEDUPARAM_H

#include <fixedUParam.h>

/**
 * @file readFixedUParam.h
 * @author Ezequiel O. Fogliatto
 * @date 20 Apr 2018
 *
 * Read parameters for fixedU boundary type
 *
 * @param fname Field name
 * @param bdname Boundary name
 * @return structure with fixed U parameters
 */

fixedUParam readFixedUParam( char* fname, char* bdname );

#endif // READFIXEDUPARAM_H
