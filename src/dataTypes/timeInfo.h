#ifndef TIMEINFO_H
#define TIMEINFO_H

#include <time.h>
#include <sys/time.h>

/**
 * @file timeInfo.h
 * @author Ezequiel O. Fogliatto
 * @date 15 Dic 2017
 * @brief Struct containing simulation parameters
 */

/**
 * @brief Struct containing simulation parameters
 *
 * This struct contains information related to global simulation 
 */

#include <dataTypes.h>


typedef struct {

    uint start;   /**< Start time */

    uint end;   /**< End time */

    uint current;   /**< Current time */

    uint writeInterval;   /**< Write interval (write every writeInterval steps) */

    time_t st;   /**< Start time (cpu time measurement) */
    
    struct timeval stt;   /**< Time struct (cpu time measurement) */

    uint stp;   /**< Time step inside write intrval */

    /* uint debug;   /\**< Debug flag. If true, write fields in raw format *\/ */


    /** Data format */

    dataFormat data;
    
    
} timeInfo;


#endif // TIMEINFO_H
