#ifndef FIXEDEOSPPARAM_H
#define FIXEDEOSPPARAM_H

/**
 * @file fixedEOSpParam.h
 * @author Ezequiel O. Fogliatto
 * @date 20 Apr 2018
 * Parameters for fixed EOS pressure boundary type
 */

typedef struct {

    /** Reference temperature */
    double T;

    /** Reference pressure */
    double p;

} fixedEOSpParam;

#endif // FIXEDEOSPPARAM_H
