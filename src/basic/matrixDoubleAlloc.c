#include <stdio.h>
#include <stdlib.h>
#include <matrixDoubleAlloc.h>

scalar** matrixDoubleAlloc(unsigned int nrow, unsigned int ncol, scalar df) {

    scalar** M = (scalar**)malloc( nrow * sizeof(scalar*) );

    unsigned int i,j;

    for( i = 0 ; i < nrow ; i++ ) {

	M[i] = (scalar*)malloc( ncol * sizeof(scalar) );

    }

    for( i = 0 ; i < nrow ; i++ ) {

	for( j = 0 ; j < ncol ; j++ ) {

	    M[i][j] = df;

	}    

    }

    return M;

}
