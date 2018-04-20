#include <liMRTDensity.h>

double liMRTDensity( latticeMesh* mesh, double* f ) {

    unsigned int k;

    double rho = 0;
    
    // Move over velocities
	
    for(k = 0 ; k < mesh->lattice.Q ; k++) {

	rho += f[k];

    }

    return rho;
	
}
