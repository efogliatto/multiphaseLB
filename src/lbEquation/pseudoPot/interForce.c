#include <stdlib.h>
#include <stdio.h>
#include <interForce.h>
#include <interactionForce.h>


void interForce( latticeMesh* mesh, macroFields* mfields ) {

    uint id, j;

    scalar F[3];
    

    // Move over points

    for( id = 0 ; id < mesh->parallel.nlocal ; id++ ) {

      
	interactionForce( mesh, F, mfields->rho, mfields->T, id );


	for( j = 0 ; j < 3 ; j++ ) {


            // Interaction force
	  
	    mfields->Fi[id][j] = F[j];



	    // Total force

	    mfields->Ft[id][j] = F[j]  +   (mfields->rho[id] - mesh->EOS.rho_0) * mesh->EOS.g[j];

	    if( mesh->mesh.isOnBnd[id] == 0 ) {
	    
		mfields->Ft[id][j] += mesh->EOS.fext[j];

	    }

	    /* else { */

	    /* 	mfields->Ft[id][j] = 0; */

	    /* } */

	}


    }

}
