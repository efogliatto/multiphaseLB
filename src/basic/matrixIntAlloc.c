#include <stdio.h>
#include <stdlib.h>

int** matrixIntAlloc(unsigned int nrow, unsigned int ncol, int df) {

    int** M = (int**)malloc( nrow * sizeof(int*) );

    unsigned int i,j;

    for( i = 0 ; i < nrow ; i++ ) {

	M[i] = (int*)malloc( ncol * sizeof(int) );

    }

    for( i = 0 ; i < nrow ; i++ ) {

	for( j = 0 ; j < ncol ; j++ ) {

	    M[i][j] = df;

	}    

    }

    return M;

}
