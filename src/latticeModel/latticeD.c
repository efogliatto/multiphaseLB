#include <latticeD.h>
#include <stdio.h>
#include <string.h>

uint latticeD( DdQq model ) {

    
    uint D = 1;
    

    switch( model ) {

	
    case D2Q9:

	D = 2;

	break;

	
    case D3Q15:

	D = 3;

	break;

	
    default:

	D = 1;

	break;

    }
    

    return D;

}
