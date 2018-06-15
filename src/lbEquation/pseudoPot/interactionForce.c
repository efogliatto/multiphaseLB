#include <stdlib.h>
#include <stdio.h>
#include <potential.h>
#include <interactionForce.h>

void interactionForce( latticeMesh* mesh, scalar Ff[3], scalar* rho, scalar* T, uint id ) {

    uint i,
	k,
	noneigh = 0;


    scalar F[3] = {0.0, 0.0, 0.0};
    
    // Initialize force term
    for( i = 0 ; i < 3 ; i++) {

    	Ff[i] = 0 ;

    }



    // Move over neighbours and check for boundary
    for( k = 1 ; k < mesh->lattice.Q ; k++ ) {

    	if( mesh->mesh.nb[id][k] == -1 ) {
	    
	    noneigh++;
	    
    	}

    }


    // Do not use unexisting neighbour
    if( noneigh == 0 ) {

	
	for( k = 1 ; k < mesh->lattice.Q ; k++ ) {
       

	    int neighId = mesh->mesh.nb[id][ mesh->lattice.reverse[k] ];
	    
    	    scalar alpha = mesh->lattice.weights[k] * potential(mesh, rho[neighId], T[neighId]);

	    
    	    for( i = 0 ; i < 3 ; i++ ) {

		F[i] +=  alpha * (scalar)mesh->lattice.vel[k][i] ;

    	    }
    

    	}

	

	

    	// Extra constant
    	scalar beta = -mesh->EOS.G * potential(mesh, rho[id], T[id]);
    
    	for( i = 0 ; i < 3 ; i++) {
	
    	    Ff[i] =  F[i] * beta;
	
    	}	

    }


    
    
    
    /* // Move over neighbours */
    /* for( k = 0 ; k < mesh->lattice.Q ; k++ ) { */

    /* 	int neighId = mesh->mesh.nb[id][k]; */

    /* 	// Do not compute interaction force (fluid-fluid) over boundary nodes */
    /* 	if( neighId == -1 ) { */
	    
    /* 	    /\* neighId = nb[ id ][ info->lattice.reverse[k] ]; *\/ */
    /* 	    noneigh++; */
	    
    /* 	} */
	
    /* 	// Do not use unexisting neighbour */
    /* 	if(  ( neighId != -1 )  &&  (noneigh == 0)  ) { */
	    
    /* 	    scalar alpha = mesh->lattice.weights[k] * potential(mesh, rho[neighId], T[neighId]); */
	    
    /* 	    for( i = 0 ; i < 3 ; i++ ) { */

    /* 		F[i] +=  alpha * mesh->lattice.vel[ mesh->lattice.reverse[k] ][i] ; */

    /* 	    } */

    /* 	} */

    /* } */
 

   

    /* if(noneigh == 0) { */
	
    /* 	// Extra constant */
    /* 	scalar beta = -mesh->EOS._G * potential(mesh, rho[id], T[id]); */
    
    /* 	for( i = 0 ; i < 3 ; i++) { */
	
    /* 	    F[i] =  F[i] * beta; */
	
    /* 	} */

    /* } */

    /* else { */

    /* 	for( i = 0 ; i < 3 ; i++) { */
	
    /* 	    F[i] =  0; */
	
    /* 	} */

    /* } */

    
    
}
