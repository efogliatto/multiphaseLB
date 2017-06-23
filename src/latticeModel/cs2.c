#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <cs2.h>

double cs2( char* modelName ) {

    double cs2 = 1;

    if ( strcmp(modelName,"D2Q9") == 0 ) {

	cs2 = D2Q9_cs2();
	
    }

    return cs2;

}
