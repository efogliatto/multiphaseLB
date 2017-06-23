#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <ppWeights.h>

double* ppWeights( char* modelName ) {

    double* w;

    if ( strcmp(modelName,"D2Q9") == 0 ) {

	w = D2Q9_ppw();
	
    }

    return w;

}
