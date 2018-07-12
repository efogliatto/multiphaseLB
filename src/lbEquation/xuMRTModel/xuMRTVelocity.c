#include <pseudoPot.h>
#include <xuMRTVelocity.h>
#include <stdlib.h>


void xuMRTVelocity( latticeMesh* mesh, macroFields* mfields, lbeField* field, scalar** v, uint id ) {

    uint j, k;

    // Interaction force
    scalar F[3];

    // Local velocity
    scalar lv[3] = {0,0,0};

	
    // Compute Total force
	
    for( j = 0 ; j < 3 ; j++ ) {

	F[j] = mfields->Fi[id][j]  +   (mfields->rho[id] - mesh->EOS.rho_0) * mesh->EOS.g[j];

    }          


    // Move over velocity components
    for( j = 0 ; j < 3 ; j++ ) {

	// Move over model velocities
	for(k = 0 ; k < mesh->mesh.Q ; k++) {

	    lv[j] += mesh->lattice.vel[k][j] * field->value[id][k];
		    
	}
	    
    }


    // Add interaction force and divide by density
    for( j = 0 ; j < 3 ; j++ ) {

	lv[j] = ( lv[j]   +   F[j] * 0.5  ) / mfields->rho[id];
	
    }


    // Copy to global array
    for(j = 0 ; j < 3 ; j++) {
	
    	v[id][j] = lv[j];
	
    }    
	
    
}
