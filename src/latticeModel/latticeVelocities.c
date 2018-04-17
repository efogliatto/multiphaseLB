#include <stdio.h>
#include <stdlib.h>
#include <latticeVelocities.h>

int** latticeVelocities( DdQq model ) {

    int** vel = NULL;

    
    switch( model ) {

	
    case D2Q9:

	vel = D2Q9_Vel();

	break;

	
    case D3Q15:

	vel = NULL;

	break;

	
    default:

	vel = NULL;

	break;

    }

    

    return vel;

}
