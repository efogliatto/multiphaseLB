#include <matVecMult.h>
#include <stdio.h>

void matVecMult(scalar** M, scalar* v, scalar* res, unsigned int n) {

    unsigned int i,j;

    for( i = 0 ; i < n ; i++ ) {

	res[i] = 0;
	
	for( j = 0 ; j < n ; j++ ) {

	    res[i] += M[i][j] * v[j];

	}

    }    
    
}
