#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cs2.h>

scalar cs2( DdQq model ) {

    scalar cs2 = 1;

    
    switch( model ) {

	
    case D2Q9:

	cs2 = D2Q9_cs2();

	break;

	
    case D3Q15:

	cs2 = D3Q15_cs2();

	break;

	
    default:

	cs2 = 1;

	break;

    }
    

    return cs2;

}
