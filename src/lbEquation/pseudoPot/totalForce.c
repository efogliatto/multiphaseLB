#include <totalForce.h>
#include <interactionForce.h>
#include <stdio.h>


void totalForce( latticeMesh* mesh, scalar F[3], scalar* rho, scalar* T, uint id ) {

    
    uint i;

    
    // Intermolecular interaction force
    
    interactionForce( mesh, F, rho, T, id );


    // Addition of body force
    
    for( i = 0 ; i < 3 ; i++) {
	
    	F[i] +=  (rho[id] - mesh->EOS.rho_0) * mesh->EOS.g[i];
	
    }

    
    
}
