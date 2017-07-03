#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>
#include <pseudoPot.h>


void liSRTVelocity( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, double v[3], unsigned int id ) {

    unsigned int j, k;

    // Interaction force
    double F[3];

	
    // Compute interaction force
    totalForce( mesh, F, mfields->rho, mfields->T, id );

	
    // Initialize velocities
    for(k = 0 ; k < 3 ; k++) {
	
	v[k] = 0;
	
    }	
	


    // Move over velocity components
    for( j = 0 ; j < 3 ; j++ ) {

	// Move over model velocities
	for(k = 0 ; k < mesh->lattice.Q ; k++) {

	    v[j] += mesh->lattice.vel[k][j] * field->value[id][k];
		    
	}
	    
    }


    // Add interaction force and divide by density
    for( j = 0 ; j < 3 ; j++ ) {

	v[j] = ( v[j]   +   F[j] * 0.5  ) / mfields->rho[id];

    }
	
    
}
