#include <stdio.h>
#include <stdlib.h>
#include <matrixDoubleAlloc.h>

double** matrixDoubleAlloc(unsigned int nrow, unsigned int ncol, double df) {

    double** M = (double**)malloc( nrow * sizeof(double*) );

    unsigned int i,j;

    for( i = 0 ; i < nrow ; i++ ) {

	M[i] = (double*)malloc( ncol * sizeof(double) );

    }

    for( i = 0 ; i < nrow ; i++ ) {

	for( j = 0 ; j < ncol ; j++ ) {

	    M[i][j] = df;

	}    

    }

    return M;

}
