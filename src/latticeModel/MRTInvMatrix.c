#include <stdio.h>
#include <stdlib.h>
#include <MRTInvMatrix.h>


double** MRTInvMatrix( DdQq model ) {

    double** invM = NULL;


    switch( model ) {

	
    case D2Q9:

	invM = D2Q9_MRTInv();

	break;

	
    case D3Q15:

	break;

	
    default:

	break;

    }
    
    

    return invM;

}
