#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>
#include <pseudoPot.h>
#include <stdlib.h>


void liMRTVelocity( latticeMesh* mesh, macroFields* mfields, lbeField* field, double** v, unsigned int id ) {

    unsigned int j, k;

    // Interaction force
    double F[3];

    // Local velocity
    double lv[3] = {0,0,0};

	
    // Compute interaction force
    /* totalForce( mesh, F, mfields->rho, mfields->T, id ); */
	
    for( j = 0 ; j < 3 ; j++ ) {

	F[j] = mfields->Fi[id][j]  +   (mfields->rho[id] - mesh->EOS.rho_0) * mesh->EOS._g[j];

    }
    

	
    /* // Initialize velocities */
    /* for(k = 0 ; k < 3 ; k++) { */
	
    /* 	v[id][k] = 0; */
	
    /* }	 */
	


    // Move over velocity components
    for( j = 0 ; j < 3 ; j++ ) {

	// Move over model velocities
	for(k = 0 ; k < mesh->mesh.Q ; k++) {

	    /* v[id][j] += mesh->lattice.vel[k][j] * field->value[id][k]; */
	    lv[j] += mesh->lattice.vel[k][j] * field->value[id][k];
		    
	}
	    
    }


    // Add interaction force and divide by density
    for( j = 0 ; j < 3 ; j++ ) {

	/* v[id][j] = ( v[id][j]   +   F[j] * 0.5  ) / mfields->rho[id]; */
	lv[j] = ( lv[j]   +   F[j] * 0.5  ) / mfields->rho[id];
	
    }


    // Copy to global array
    for(j = 0 ; j < 3 ; j++) {
	
    	v[id][j] = lv[j];
	
    }    
	
    
}
