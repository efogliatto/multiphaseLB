#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <latticeWeights.h>

double* latticeWeights( char* modelName ) {

    double* omega = NULL;

    if ( strcmp(modelName,"D2Q9") == 0 ) {

	omega = D2Q9_omega();
	
    }

    return omega;

}
