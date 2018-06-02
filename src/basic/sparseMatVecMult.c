#include <sparseMatVecMult.h>
#include <stdio.h>

void sparseMatVecMult(double** M, double* v, double* res, unsigned int** nonZero, unsigned int n, unsigned int nextra) {
    
    unsigned int i,j,k;


    /* Compute diagonal elements */

    for( i = 0 ; i < n ; i++ ) {

	res[i] = M[i][i] * v[i];
	
    }


    /* Add off-diagonal elements */

    for( i = 0 ; i < nextra ; i++ ) {

	j = nonZero[i][0];

	k = nonZero[i][1];

	res[j] = res[j] + M[j][k] * v[k];

    }
    
}
