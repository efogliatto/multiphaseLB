#ifndef UHEATFLUXPARAM_H
#define UHEATFLUXPARAM_H

/**
 * @file uHeatFluxParam.h
 * @author Ezequiel O. Fogliatto
 * @date 20 Apr 2018
 * Parameters for uniform heat flux boundary type
 */

#include <dataTypes.h>

typedef struct {

    /** Fixed heat flux at boundary */
    scalar q[3];

} uHeatFluxParam;

#endif // UHEATFLUXPARAM_H
