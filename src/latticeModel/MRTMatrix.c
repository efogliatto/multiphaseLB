#include <stdio.h>
#include <stdlib.h>
#include <MRTMatrix.h>


scalar** MRTMatrix( DdQq model ) {

    scalar** M = NULL;


    switch( model ) {

	
    case D2Q9:

	M = D2Q9_MRT();

	break;

	
    case D3Q15:

	M = D3Q15_MRT();

	break;

	
    default:

	break;

    }
    

    return M;

}
