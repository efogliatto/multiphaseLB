#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <latticeVelocities.h>

int** latticeVelocities( char* modelName ) {

    int** vel = NULL;

    if ( strcmp(modelName,"D2Q9") == 0 ) {

	vel = D2Q9_Vel();
	
    }

    return vel;

}
