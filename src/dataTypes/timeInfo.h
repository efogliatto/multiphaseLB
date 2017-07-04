#ifndef TIMEINFO_H
#define TIMEINFO_H

#include <time.h>
#include <sys/time.h>

struct timeInfo {

    // Simulation parameters

    // Start time
    unsigned int start;

    // End time
    unsigned int end;

    // Current time
    unsigned int current;


    // Write interval (write every writeInterval steps)
    unsigned int writeInterval;

    // Start time (time measurement)
    time_t st;
    struct timeval stt;

    // Time step (inside write intrval)
    unsigned int stp;

    // Debug flag
    unsigned int debug;
    
    
};


#endif // TIMEINFO_H
