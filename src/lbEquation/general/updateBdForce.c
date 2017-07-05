#include <macroFields.h>
#include <latticeMesh.h>
#include <pseudoPot.h>

void updateBdForce( struct latticeMesh* mesh, struct macroFields* mfields ) {

    
    unsigned int bndId,
	i,
	j,
	k;

    double F[3];

    
    // Move over boundaries
    
    for( bndId = 0 ; bndId < mesh->mesh.bd.nbd ; bndId++ ) {


	// Move over boundary elements
	    
	for( i = 0 ; i < mesh->mesh.bd.nbdelem[bndId] ; i++ ) {


	    j = mesh->mesh.bd.bdPoints[bndId][i];


	    interactionForce( mesh, F, mfields->rho, mfields->T, j );

	    
	    for( k = 0 ; k < 3 ; k++ ) {
	
	    	mfields->Fi[j][k] = F[k];

	    }


	}
	
    }
    

    
}
