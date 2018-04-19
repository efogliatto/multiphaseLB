#ifndef READLIMRTCONSTANTS_H
#define READLIMRTCONSTANTS_H

#include <liMRTConstants.h>

/**
 * @file readLiMRTConstants.h
 * @author Ezequiel O. Fogliatto
 * @date 19 Apr 2019
 * Read constants for li MRT model from properties/macroProperties
 * @param fname Field name
 * @return Structure with constants
 */

liMRTConstants readLiMRTConstants( char* fname );

#endif // READLIMRTCONSTANTS_H
