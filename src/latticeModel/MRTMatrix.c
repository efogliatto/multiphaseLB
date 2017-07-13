#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <MRTMatrix.h>

double** MRTMatrix( char* modelName ) {

    double** M = NULL;

    if ( strcmp(modelName,"D2Q9") == 0 ) {

	M = D2Q9_MRT();
	
    }

    return M;

}
