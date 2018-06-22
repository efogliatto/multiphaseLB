#ifndef FIXEDRANDOMTPARAM_H
#define FIXEDRANDOMTPARAM_H

/**
 * @file fixedRandomTParam.h
 * @author Ezequiel O. Fogliatto
 * @date 20 Apr 2018
 * Parameters for fixedRandomT boundary type
 */

#include <dataTypes.h>

typedef struct {

    /** Fixed temperature value at boundary */
    scalar T;

    /** Temperature perturbation */
    scalar p;

    /** Perturbation length (time steps) */
    int psteps;

    /** Perturbation local time step */
    int localTStep;

} fixedRandomTParam;

#endif // FIXEDRANDOMTPARAM_H
