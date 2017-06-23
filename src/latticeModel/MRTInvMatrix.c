#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <MRTInvMatrix.h>

double** MRTInvMatrix( char* modelName ) {

    double** invM;

    if ( strcmp(modelName,"D2Q9") == 0 ) {

	invM = D2Q9_MRTInv();
	
    }

    return invM;

}
