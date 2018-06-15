#include <stdio.h>
#include <stdlib.h>
#include <fixedU.h>
#include <liMRTEquilibrium.h>


void fixedU( latticeMesh* mesh, macroFields* mfields, scalar** field, uint bid, lbeModel model, bdParam* bp, lbParameters* lp ) {


    if( model == liMRT ) {

	
	unsigned int i, k;

	scalar* f_eq_nb = (scalar*)malloc( mesh->mesh.Q * sizeof(scalar) );

	scalar* f_eq_bnd  = (scalar*)malloc( mesh->mesh.Q * sizeof(scalar) );
	

    
	// Velocity at boundary

	scalar Uw[3];
	Uw[0] = bp->fu.U[0];
	Uw[1] = bp->fu.U[1];
	Uw[2] = bp->fu.U[2];
    
    
	// Move over boundary elements

	for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) {

	
	    uint id = mesh->mesh.bd.bdPoints[bid][i];
	
	
	    // Move over lattice velocities
	    
	    for( k = 0 ; k < mesh->mesh.Q ; k++ ) {


		if ( mesh->mesh.nb[id][k] == -1 ) {

		
		    // Need density and velocity at neighbour (reverse) node
		    
		    int nbid = mesh->mesh.nb[id][ mesh->lattice.reverse[k] ];


		    if( nbid != -1 ) {

			liMRTEquilibrium( &mesh->lattice, mfields->rho[nbid], mfields->U[nbid], f_eq_nb );

			liMRTEquilibrium( &mesh->lattice, mfields->rho[nbid], Uw, f_eq_bnd );
		    

			// Update distribution
			
			field[id][k] = f_eq_bnd[k] + (field[nbid][k] - f_eq_nb[k] );

		    }
		

		}

	    }

	}
	

    }

}
