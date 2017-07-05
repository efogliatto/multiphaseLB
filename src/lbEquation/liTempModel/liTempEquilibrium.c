#include <latticeInfo.h>
#include <stdio.h>

void liTempEquilibrium( struct latticeInfo* lattice, double rho, double v[3], double* f ) {

    unsigned int k, j;

    // Move over velocities
    
    for( k = 0 ; k < lattice->Q ; k++ ) {

    	double alpha = 0,
    	    beta = 0;

    	// Dot product
	
    	for( j = 0 ; j < 3 ; j++ ) {

    	    alpha += lattice->vel[k][j] * v[j];

    	    beta += v[j] * v[j];

    	}

    	f[k] = rho * lattice->omega[k] * ( 1 + alpha/lattice->cs2   /* +   0.5 * alpha * alpha / (lattice->cs2*lattice->cs2)  -  0.5 * beta / lattice->cs2 */ );
	

    }

}
