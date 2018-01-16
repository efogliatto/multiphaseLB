#include <stdio.h>
#include <string.h>

unsigned int latticeD( char* modelName ) {

    unsigned int D;
    
    if ( strcmp(modelName,"D2Q9") == 0 ) {

	D = 2;
	
    }

    return D;

}
