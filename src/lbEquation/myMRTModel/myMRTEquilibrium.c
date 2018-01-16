#include <latticeInfo.h>

void myMRTEquilibrium( struct latticeInfo* lattice, double rho, double v[3], double* f ) {

    unsigned int k, j;

    // Move over velocities
    
    for( k = 0 ; k < lattice->Q ; k++ ) {

	f[k] = 0;

    }

}
