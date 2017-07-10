#include <stdio.h>
#include <stdlib.h>
#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>
#include <liTempEquilibrium.h>
#include <liMRTEquilibrium.h>


void fixedU( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int bid ) {

    
    unsigned int i, k;

    double* f_eq_nb = (double*)malloc( mesh->mesh.Q * sizeof(double) );

    double* f_eq_bnd  = (double*)malloc( mesh->mesh.Q * sizeof(double) );
	

    
    // Velocity at boundary

    double Uw[3];
    Uw[0] = field->boundary[bid].vectorVal[0];
    Uw[1] = field->boundary[bid].vectorVal[1];
    Uw[2] = field->boundary[bid].vectorVal[2];
    
    
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
			
		    field->value[id][k] = f_eq_bnd[k] + (field->value[nbid][k] - f_eq_nb[k] );		    

		}
		

	    }

	}



	
	

    }

}
