#ifndef MYMRTCONSTANTS_H
#define MYMRTCONSTANTS_H

/**
 * @file myMRTConstants.h
 * @author Ezequiel O. Fogliatto
 * @date 19 Apr 2019
 * Constants for my MRT model
 */

#include <dataTypes.h>

typedef struct {

    /** Multiple relaxation times */
    scalar* Lambda;

    /** Thermal conductivity */
    scalar lambda;
        
    /** Extra constants used for equilibrium distributions in moment space (myMRTModel) */
    scalar alpha_1;

    scalar alpha_2;    
    

} myMRTConstants;

#endif // MYMRTCONSTANTS_H
