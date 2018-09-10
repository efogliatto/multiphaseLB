#ifndef FIXEDGRADTPARAM_H
#define FIXEDGRADTPARAM_H

/**
 * @file fixedGradTParam.h
 * @author Ezequiel O. Fogliatto
 * @date 20 Apr 2018
 * Parameters for fixedGradT boundary type
 */

#include <dataTypes.h>

typedef struct {

    /** Fixed temperature value at boundary */
    scalar gradT;

    /** Velocity asociated to normal */
    uint nv;

    /** Temperature perturbation */
    scalar pert;

    /* /\** Perturbation length (time steps) *\/ */
    /* int psteps; */

    /* /\** Perturbation local time step *\/ */
    /* int localTStep; */

} fixedGradTParam;

#endif // FIXEDGRADTPARAM_H
