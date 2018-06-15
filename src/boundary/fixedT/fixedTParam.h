#ifndef FIXEDTPARAM_H
#define FIXEDTPARAM_H

/**
 * @file fixedTParam.h
 * @author Ezequiel O. Fogliatto
 * @date 20 Apr 2018
 * Parameters for fixedT boundary type
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

} fixedTParam;

#endif // FIXEDTPARAM_H
