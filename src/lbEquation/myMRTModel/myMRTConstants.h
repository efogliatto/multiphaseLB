#ifndef MYMRTCONSTANTS_H
#define MYMRTCONSTANTS_H

/**
 * @file myMRTConstants.h
 * @author Ezequiel O. Fogliatto
 * @date 19 Apr 2019
 * Constants for my MRT model
 */

typedef struct {

    /** Multiple relaxation times */
    double* Lambda;

    /** Thermal conductivity */
    double lambda;
        
    /** Extra constants used for equilibrium distributions in moment space (myMRTModel) */
    double alpha_1;

    double alpha_2;    
    

} myMRTConstants;

#endif // MYMRTCONSTANTS_H
