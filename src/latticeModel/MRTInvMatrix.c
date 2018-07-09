#include <stdio.h>
#include <stdlib.h>
#include <MRTInvMatrix.h>


scalar** MRTInvMatrix( DdQq model ) {

    scalar** invM = NULL;


    switch( model ) {

	
    case D2Q9:

	invM = D2Q9_MRTInv();

	break;

	
    case D3Q15:

	invM = D3Q15_MRTInv();

	break;

	
    default:

	break;

    }
    
    

    return invM;

}
