#include <stdio.h>
#include <stdlib.h>
#include <basic.h>
#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>
/* #include <myMRTEquilibrium.h> */
#include <singleNodeT.h>
#include <lbeModel.h>
#include <lbEquation.h>
#include <fixedT.h>
#include <time.h>


void fixedT( latticeMesh* mesh, macroFields* mfields, scalar** field, unsigned int bid, lbeModel model, bdParam* bp, lbParameters* lp ) {



    // Apply only if collision model is myMRT
      
	
    uint i, k;

    scalar* f_eq_nb = (scalar*)malloc( mesh->mesh.Q * sizeof(scalar) );

    scalar eq_bnd = 0;
	
    scalar eq_nb = 0;
		
    
    // Move over boundary elements

    for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) {

	
	uint id = mesh->mesh.bd.bdPoints[bid][i];

	
	
	// Move over lattice velocities
	    
	for( k = 0 ; k < mesh->mesh.Q ; k++ ) {


	    if ( mesh->mesh.nb[id][k] == -1 ) {


		// Need density and velocity at neighbour (reverse) node
		    
		int nbid = mesh->mesh.nb[id][ mesh->lattice.reverse[k] ];
		    
		if( nbid != -1 ) {

			    
		    // Equilibrium at neighbour node

		    switch( model ) {

		    case myMRT:
			    
			myMRTEquilibrium( &mesh->lattice, mfields->T[nbid], mfields->U[nbid], lp->myMRT.alpha_1, lp->myMRT.alpha_2, f_eq_nb );

			break;


		    case liTempMRT:

			liTempMRTEquilibrium( &mesh->lattice, mfields->T[nbid], mfields->U[nbid], f_eq_nb );

			break;


		    default:

			errorMsg("Unable to apply boundary condition on temperature");

			break;
			    

		    }



			
			    
		    eq_nb  = f_eq_nb[k];


		    // Equilibrium at boundary node

		    switch( model )  {

		    case myMRT:

			myMRTEquilibrium( &mesh->lattice, bp->ft.T, mfields->U[nbid], lp->myMRT.alpha_1, lp->myMRT.alpha_2, f_eq_nb );

			break;

		    case liTempMRT:

			liTempMRTEquilibrium( &mesh->lattice, bp->ft.T, mfields->U[nbid], f_eq_nb );

			break;


		    default:

			errorMsg("Unable to apply boundary condition on temperature");

			break;			

		    }


		    
		    eq_bnd = f_eq_nb[k];
			    

			
		    // Update distribution
			
		    field[id][k] = eq_bnd + (field[nbid][k] - eq_nb);

		}
		

	    }

	}
	
	

    }


    free(f_eq_nb);


    
           

}
