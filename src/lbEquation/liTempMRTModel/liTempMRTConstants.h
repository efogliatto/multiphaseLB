#ifndef LITEMPMRTCONSTANTS_H
#define LITEMPMRTCONSTANTS_H

/**
 * @file liTempMRTConstants.h
 * @author Ezequiel O. Fogliatto
 * @date 19 Apr 2019
 * Constants for li MRT model
 */

#include <dataTypes.h>

typedef struct {

    /** Multiple relaxation times */
    scalar* Lambda;

    /** Thermal conductivity */
    scalar lambda;            

} liTempMRTConstants;

#endif // LITEMPMRTCONSTANTS_H
