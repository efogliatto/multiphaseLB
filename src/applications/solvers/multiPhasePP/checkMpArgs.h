#ifndef CHECKMPARGS_H
#define CHECKMPARGS_H

#include <dataTypes.h>


// Solver options

typedef struct {

    uint ht;

    uint frozen;

    uint mthread;    

} mpOptions;



mpOptions checkMpArgs( int argc, char **argv );

#endif // CHECKMPARGS_H
