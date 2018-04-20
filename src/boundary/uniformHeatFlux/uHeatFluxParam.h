#ifndef UHEATFLUXPARAM_H
#define UHEATFLUXPARAM_H

/**
 * @file uHeatFluxParam.h
 * @author Ezequiel O. Fogliatto
 * @date 20 Apr 2018
 * Parameters for uniform heat flux boundary type
 */

typedef struct {

    /** Fixed heat flux at boundary */
    double q[3];

} uHeatFluxParam;

#endif // UHEATFLUXPARAM_H
