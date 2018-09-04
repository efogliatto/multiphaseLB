#include <stdlib.h>
#include <stdio.h>
#include <potential.h>
#include <interactionForce.h>
/* #include <time.h> */


void interactionForce( latticeMesh* mesh, scalar Ff[3], scalar* rho, scalar* T, uint id ) {

    uint i,
	k;



    
    /* // EOS Perturbation. Temporal    */
    
    /* scalar r = 1; */

    /* if (mesh->mesh.points[id][1] == 0) { */
    
    /* 	srand(id);     */

    /* 	r = (scalar)rand() / RAND_MAX; */

    /* 	r = 0.9 + (1.1-0.9)*r; */

    /* } */


    
    scalar F[3] = {0.0, 0.0, 0.0};
    
    // Initialize force term
    for( i = 0 ; i < 3 ; i++) {

    	Ff[i] = 0 ;

    }




    // Do not use unexisting neighbour
    if( mesh->mesh.isOnBnd[id] == 0 ) {

	
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
    
    
}
