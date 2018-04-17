#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cs2.h>

double cs2( DdQq model ) {

    double cs2 = 1;

    
    switch( model ) {

	
    case D2Q9:

	cs2 = D2Q9_cs2();

	break;

	
    case D3Q15:

	cs2 = 1.0 / 3.0;

	break;

	
    default:

	cs2 = 1;

	break;

    }
    

    return cs2;

}
