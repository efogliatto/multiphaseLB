#ifndef FIXEDUPARAM_H
#define FIXEDUPARAM_H

/**
 * @file fixedUParam.h
 * @author Ezequiel O. Fogliatto
 * @date 20 Apr 2018
 * Parameters for fixedU boundary type
 */

typedef struct {

    /** Fixed velocity value at boundary */
    double U[3];

} fixedUParam;

#endif // FIXEDUPARAM_H
