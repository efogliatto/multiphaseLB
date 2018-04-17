#include <stdio.h>
#include <stdlib.h>
#include <latticeWeights.h>

double* latticeWeights( DdQq model ) {

    double* omega = NULL;


    switch( model ) {

	
    case D2Q9:

	omega = D2Q9_omega();

	break;

	
    case D3Q15:

	omega = NULL;

	break;

	
    default:

	omega = NULL;

	break;

    }

    

    return omega;

}
