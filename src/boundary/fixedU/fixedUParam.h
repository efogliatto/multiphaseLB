#ifndef FIXEDUPARAM_H
#define FIXEDUPARAM_H

/**
 * @file fixedUParam.h
 * @author Ezequiel O. Fogliatto
 * @date 20 Apr 2018
 * Parameters for fixedU boundary type
 */
#include <dataTypes.h>

typedef struct {

    /** Fixed velocity value at boundary */
    scalar U[3];

} fixedUParam;

#endif // FIXEDUPARAM_H
