#include <stdio.h>
#include <string.h>
#include <latticeQ.h>

uint latticeQ( DdQq model ) {

    uint Q;

    
    switch( model ) {

	
    case D2Q9:

	Q = 9;

	break;

	
    case D3Q15:

	Q = 15;

	break;

	
    default:

	Q = 0;

	break;

    }
    
    
    return Q;

}
