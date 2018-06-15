#ifndef FIXEDEOSPPARAM_H
#define FIXEDEOSPPARAM_H

/**
 * @file fixedEOSpParam.h
 * @author Ezequiel O. Fogliatto
 * @date 20 Apr 2018
 * Parameters for fixed EOS pressure boundary type
 */

#include <dataTypes.h>

typedef struct {

    /** Reference temperature */
    scalar T;

    /** Reference pressure */
    scalar p;

} fixedEOSpParam;

#endif // FIXEDEOSPPARAM_H
