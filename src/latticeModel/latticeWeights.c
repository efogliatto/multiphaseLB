#include <stdio.h>
#include <stdlib.h>
#include <latticeWeights.h>

scalar* latticeWeights( DdQq model ) {

    scalar* omega = NULL;


    switch( model ) {

	
    case D2Q9:

	omega = D2Q9_omega();

	break;

	
    case D3Q15:

	omega = D3Q15_omega();

	break;

	
    default:

	omega = NULL;

	break;

    }

    

    return omega;

}
