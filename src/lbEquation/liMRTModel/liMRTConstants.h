#ifndef LIMRTCONSTANTS_H
#define LIMRTCONSTANTS_H

/**
 * @file liMRTConstants.h
 * @author Ezequiel O. Fogliatto
 * @date 19 Apr 2019
 * Constants for li MRT model
 */

typedef struct {

    /** Multiple relaxation times */
    double* Lambda;

    /** Force coefficient */
    double sigma;

    /** Extra constants used for tau dependency */
    double ra;

    /** Extra constants used for tau dependency */
    double rb;

    /** Extra constants used for tau dependency */
    double na;

    /** Extra constants used for tau dependency */
    double nb;
    

} liMRTConstants;

#endif // LIMRTCONSTANTS_H
