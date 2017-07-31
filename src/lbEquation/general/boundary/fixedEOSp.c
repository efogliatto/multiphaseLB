#include <stdio.h>
#include <stdlib.h>
#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>
#include <liTempEquilibrium.h>
#include <pseudoPot.h>


void fixedEOSp( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int bid ) {


    // Apply only if collision model is liTemp
    // Compute T from T_eos. Use boundary value for T and rho

    if(  ( field->colId == 2 ) ||  ( field->colId == 3 )  ){

	
	unsigned int i, k;

	double* f_eq_nb = (double*)malloc( mesh->mesh.Q * sizeof(double) );

	double eq_bnd = 0;
	
	double eq_nb = 0;

	
	srand( time(NULL) );
	
    
	// Move over boundary elements

	for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) {

	
	    unsigned int id = mesh->mesh.bd.bdPoints[bid][i];


	    // Update T boundary val

	    double p_bd = p_eos(&mesh->EOS, field->boundary[bid].vectorVal[0], field->boundary[bid].vectorVal[1]);

	    double t_bd = T_eos(&mesh->EOS, mfields->rho[id], p_bd);
	    

	    
	    // Move over lattice velocities
	    
	    for( k = 0 ; k < mesh->mesh.Q ; k++ ) {


		if ( mesh->mesh.nb[id][k] == -1 ) {


		    // Need density and velocity at neighbour (reverse) node
		    
		    int nbid = mesh->mesh.nb[id][ mesh->lattice.reverse[k] ];		    
		    
		    if( nbid != -1 ) {
			
			
			liTempEquilibrium( &mesh->lattice, mfields->rho[nbid], mfields->U[nbid], f_eq_nb );
		
			eq_bnd = mesh->EOS._Cv * t_bd * f_eq_nb[k];
			    
			eq_nb  = mesh->EOS._Cv * mfields->T[nbid] * f_eq_nb[k];

			
			// Update distribution
			
			field->value[id][k] = eq_bnd + (field->value[nbid][k] - eq_nb);

		    }
		

		}

	    }




	
	

	}


	free(f_eq_nb);


    }


    else {

	printf("\n  [ERROR]  Unable to apply boundary condition on temperature\n\n");

	exit(1);

    }
    

}
