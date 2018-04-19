#ifndef LBPARAMETERS_H
#define LBPARAMETERS_H

#include <liMRTConstants.h>
#include <myMRTConstants.h>

/**
 * @file lbParameters.h
 * @author Ezequiel O. Fogliatto
 * @date 19 Apr 2019
 * Constants for lb models
 */

typedef union {

    /** Li et al. MRT Model */
    liMRTConstants liMRT;

    /** My MRT Model */
    myMRTConstants myMRT;    

} lbParameters;

#endif // LBPARAMETERS_H