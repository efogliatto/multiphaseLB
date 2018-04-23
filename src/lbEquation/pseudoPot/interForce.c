#include <stdlib.h>
#include <stdio.h>
#include <interForce.h>
#include <interactionForce.h>


void interForce( latticeMesh* mesh, macroFields* mfields ) {

    unsigned int id, j;

    double F[3];
    

    // Move over points

    for( id = 0 ; id < mesh->parallel.nlocal ; id++ ) {
	
	interactionForce( mesh, F, mfields->rho, mfields->T, id );

	for( j = 0 ; j < 3 ; j++ ) {
	
	    mfields->Fi[id][j] = F[j];

	}

    }
    
}
