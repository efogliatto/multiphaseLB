#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <latticeReverseDir.h>

int* latticeReverseDir( char* modelName ) {

    int* vel = NULL;

    if ( strcmp(modelName,"D2Q9") == 0 ) {

	vel = D2Q9_Reverse();
	
    }

    return vel;

}
