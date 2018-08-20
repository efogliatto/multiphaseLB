#ifndef LBPARAMETERS_H
#define LBPARAMETERS_H

#include <liMRTConstants.h>
#include <liTempMRTConstants.h>
#include <myMRTConstants.h>
#include <xuMRTConstants.h>

/**
 * @file lbParameters.h
 * @author Ezequiel O. Fogliatto
 * @date 19 Apr 2019
 * Constants for lb models
 */

typedef union {

    /** Li et al. MRT Model */
    liMRTConstants liMRT;

    /** Li et al. MRT Model */
    liTempMRTConstants liTempMRT;
    
    /** My MRT Model */
    myMRTConstants myMRT;

    /** Xu MRT Model */
    xuMRTConstants xuMRT;    
    

} lbParameters;

#endif // LBPARAMETERS_H
