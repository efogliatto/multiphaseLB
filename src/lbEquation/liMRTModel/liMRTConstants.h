#ifndef LIMRTCONSTANTS_H
#define LIMRTCONSTANTS_H

/**
 * @file liMRTConstants.h
 * @author Ezequiel O. Fogliatto
 * @date 19 Apr 2019
 * Constants for li MRT model
 */

#include <dataTypes.h>

typedef enum {

    no_st,

    liSurfTen

} stModel;



typedef struct {

    /** Multiple relaxation times */
    scalar* Lambda;

    /** Force coefficient */
    scalar sigma;

    /** Extra constants used for tau dependency */
    scalar ra;

    /** Extra constants used for tau dependency */
    scalar rb;

    /** Extra constants used for tau dependency */
    scalar na;

    /** Extra constants used for tau dependency */
    scalar nb;

    /** Surface tension model */
    stModel surfaceTension;

    /** Surface tension constants */
    scalar kappa_st;
    

} liMRTConstants;

#endif // LIMRTCONSTANTS_H
