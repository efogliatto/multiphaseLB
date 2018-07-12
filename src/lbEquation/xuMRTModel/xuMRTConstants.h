#ifndef XUMRTCONSTANTS_H
#define XUMRTCONSTANTS_H

/**
 * @file xuMRTConstants.h
 * @author Ezequiel O. Fogliatto
 * @date 10 Jul 2018
 * Constants for xu MRT model
 */

#include <dataTypes.h>

typedef enum {

    noXuSurf,

    xuSurfTen

} xuStModel;



typedef struct {

    /** Multiple relaxation times */
    scalar* Lambda;

    /** Force coefficient */
    scalar sigma;

    /* /\** Extra constants used for tau dependency *\/ */
    /* scalar ra; */

    /* /\** Extra constants used for tau dependency *\/ */
    /* scalar rb; */

    /* /\** Extra constants used for tau dependency *\/ */
    /* scalar na; */

    /* /\** Extra constants used for tau dependency *\/ */
    /* scalar nb; */

    /** Surface tension model */
    xuStModel surfaceTension;

    /** Surface tension constants */
    scalar kappa_st;
    

} xuMRTConstants;

#endif // xuMRTCONSTANTS_H
