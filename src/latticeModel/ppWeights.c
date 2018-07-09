#include <stdio.h>
#include <stdlib.h>
#include <ppWeights.h>


scalar* ppWeights( DdQq model ) {

    scalar* w = NULL;


    switch( model ) {

	
    case D2Q9:

	w = D2Q9_ppw();

	break;

	
    case D3Q15:

	w = D3Q15_ppw();

	break;

	
    default:

	break;

    }
	


    return w;

}
