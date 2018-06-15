#include <liMRTDensity.h>

scalar liMRTDensity( latticeMesh* mesh, scalar* f ) {

    uint k;

    scalar rho = 0;
    
    // Move over velocities
	
    for(k = 0 ; k < mesh->lattice.Q ; k++) {

	rho += f[k];

    }

    return rho;
	
}
