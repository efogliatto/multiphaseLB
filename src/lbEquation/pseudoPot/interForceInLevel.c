#include <stdlib.h>
#include <stdio.h>
#include <interForceInLevel.h>
#include <interactionForce.h>


void interForceInLevel( latticeMesh* mesh, macroFields* mfields, uint level ) {

    uint id, j;

    scalar F[3];
    

    // Move over points

    for( id = 0 ; id < mesh->mesh.nPoints ; id++ ) {

	if( mesh->parallel.level[id] == level ) {
	
	    interactionForce( mesh, F, mfields->rho, mfields->T, id );

	    for( j = 0 ; j < 3 ; j++ ) {
	
		mfields->Fi[id][j] = F[j];

	    }

	}

    }
    
}
