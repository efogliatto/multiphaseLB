#include <stdio.h>
#include <stdlib.h>
#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>
#include <liTempEquilibrium.h>
#include <liMRTEquilibrium.h>


/* void outflow( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int bid ) { */

    
/*     unsigned int i, j, k; */

/*     double* f_eq_nb = (double*)malloc( mesh->mesh.Q * sizeof(double) ); */

/*     double* f_eq_bnd  = (double*)malloc( mesh->mesh.Q * sizeof(double) ); */
	

    
/*     // Velocity at boundary */

/*     double Uw[3]; */

    
    
/*     // Move over boundary elements */

/*     for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) { */

	
/* 	unsigned int id = mesh->mesh.bd.bdPoints[bid][i]; */

	
/* 	// Move over principal directions only */

/* 	for( j = 1 ; j <= 4 ; j++ ) { */
	

/* 	    // Copy from reverse point if neighbour is not present */
	    
/* 	    if( mesh->mesh.nb[id][j] == -1 ) { */

		
/* 		Uw[0] = mfields->U[ mesh->mesh.nb[id][mesh->lattice.reverse[j]] ][0]; */
/* 		Uw[1] = mfields->U[ mesh->mesh.nb[id][mesh->lattice.reverse[j]] ][1]; */
/* 		Uw[2] = mfields->U[ mesh->mesh.nb[id][mesh->lattice.reverse[j]] ][2]; */
		
	    
/* 		// Move over lattice velocities */
	    
/* 		for( k = 0 ; k < mesh->mesh.Q ; k++ ) { */


/* 		    if ( mesh->mesh.nb[id][k] == -1 ) { */

		
/* 			// Need density and velocity at neighbour (reverse) node */
		    
/* 			int nbid = mesh->mesh.nb[id][ mesh->lattice.reverse[k] ];		     */


/* 			if( nbid != -1 ) { */

/* 			    liMRTEquilibrium( &mesh->lattice, mfields->rho[nbid], mfields->U[nbid], f_eq_nb ); */

/* 			    liMRTEquilibrium( &mesh->lattice, mfields->rho[nbid], Uw, f_eq_bnd ); */
		    

/* 			    // Update distribution */
			
/* 			    field->value[id][k] = f_eq_bnd[k] + (field->value[nbid][k] - f_eq_nb[k] );		     */

/* 			} */
		

/* 		    } */

/* 		} */


/* 	    } */
	    
/* 	} */
	
	

/*     } */

/* } */



void outflow( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int bid ) {

    unsigned int i, j, k;
    

    // Move over boundary elements
    
    for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) {

	int id = mesh->mesh.bd.bdPoints[bid][i];


	// Move over principal directions only

	for( j = 1 ; j <= 4 ; j++ ) {

	    
	    // Copy from reverse point if neighbour is not present
	    
	    if( mesh->mesh.nb[id][j] == -1 ) {


		unsigned int nid = mesh->mesh.nb[id][ mesh->lattice.reverse[j] ];
		

		// Move over lattice velocities and copy info
	
		for( k = 0 ; k < mesh->mesh.Q ; k++ ) {

		    field->value[id][k] = field->value[nid][k];

		}

		

	    }
	    
       

	}
	

    }

}
