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

struct timeInfo {

    unsigned int start;   /**< Start time */

    unsigned int end;   /**< End time */

    unsigned int current;   /**< Current time */

    unsigned int writeInterval;   /**< Write interval (write every writeInterval steps) */

    time_t st;   /**< Start time (cpu time measurement) */
    
    struct timeval stt;   /**< Time struct (cpu time measurement) */

    unsigned int stp;   /**< Time step inside write intrval */

    unsigned int debug;   /**< Debug flag. If true, write fields in raw format */   
    
};


#endif // TIMEINFO_H
