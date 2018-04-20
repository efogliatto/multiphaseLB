#include <stdio.h>
#include <stdlib.h>
#include <fixedU.h>
#include <liMRTEquilibrium.h>


void fixedU( latticeMesh* mesh, macroFields* mfields, double** field, unsigned int bid, lbeModel model, bdParam* bp, lbParameters* lp ) {


    if( model == liMRT ) {

	
	unsigned int i, k;

	double* f_eq_nb = (double*)malloc( mesh->mesh.Q * sizeof(double) );

	double* f_eq_bnd  = (double*)malloc( mesh->mesh.Q * sizeof(double) );
	

    
	// Velocity at boundary

	double Uw[3];
	Uw[0] = bp->fu.U[0];
	Uw[1] = bp->fu.U[1];
	Uw[2] = bp->fu.U[2];
    
    
	// Move over boundary elements

	for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) {

	
	    unsigned int id = mesh->mesh.bd.bdPoints[bid][i];
	
	
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
