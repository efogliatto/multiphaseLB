#include <stdio.h>
#include <stdlib.h>
#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>
#include <liTempEquilibrium.h>


void fixedT( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int bid ) {


    // Apply only if collision model is liTemp

    if( field->colId == 2 ) {

	
	unsigned int i, k;

	double* f_eq_nb = (double*)malloc( mesh->lattice.Q * sizeof(double) );

	double eq_bnd = 0;
	
	double eq_nb = 0;

	
    
	// Move over boundary elements

	for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) {

	
	    unsigned int id = mesh->mesh.bd.bdPoints[bid][i];

	    /* unsigned int noneigh = 0; */
	
	
	    // Move over lattice velocities
	    
	    for( k = 0 ; k < mesh->lattice.Q ; k++ ) {


		if ( mesh->mesh.nb[id][k] == -1 ) {


		    // Need density and velocity at neighbour (reverse) node
		    
		    int nbid = mesh->mesh.nb[id][ mesh->lattice.reverse[k] ];

		    
		    
		    if( nbid != -1 ) {

			liTempEquilibrium( &mesh->lattice, mfields->rho[nbid], mfields->U[nbid], f_eq_nb );
			
			eq_bnd = mesh->EOS._Cv * field->boundary[bid].scalarVal * f_eq_nb[k];
			    
			eq_nb  = mesh->EOS._Cv * mfields->T[nbid] * f_eq_nb[k];


			
			// Update distribution
			
			field->value[id][k] = eq_bnd + (field->value[nbid][k] - eq_nb);

		    }


		    /* else { */

		    /* 	noneigh++; */

		    /* } */
		

		}

	    }


	    /* // Apply correction for corners */
	    /* if( noneigh != 0 ) { */

	    
	    /* } */




	
	

	}


	free(f_eq_nb);


    }


    else {

	printf("\n  [ERROR]  Unable to apply boundary condition on temperature\n\n");

	exit(1);

    }
    

}
