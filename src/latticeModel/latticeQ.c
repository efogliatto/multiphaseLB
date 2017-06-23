#include <stdio.h>
#include <string.h>

#include <latticeWeights.h>

unsigned int latticeQ( char* modelName ) {

    unsigned int Q;
    
    if ( strcmp(modelName,"D2Q9") == 0 ) {

	Q = 9;
	
    }

    return Q;

}
