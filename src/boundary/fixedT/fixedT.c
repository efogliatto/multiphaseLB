#include <stdio.h>
#include <stdlib.h>
#include <basic.h>
#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>
#include <myMRTEquilibrium.h>
#include <singleNodeT.h>
#include <lbeModel.h>
#include <fixedT.h>
#include <time.h>


void fixedT( latticeMesh* mesh, macroFields* mfields, scalar** field, unsigned int bid, lbeModel model, bdParam* bp, lbParameters* lp ) {



    // Apply only if collision model is myMRT
   
    if( model == myMRT ) {

	
	uint i, k;

	scalar* f_eq_nb = (scalar*)malloc( mesh->mesh.Q * sizeof(scalar) );

	scalar eq_bnd = 0;
	
	scalar eq_nb = 0;



	/* // Perturbation conditions */

	/* srand(0); */

	/* scalar minT = bp->ft.T * (100.0-bp->ft.p) / 100.0; */

	/* scalar maxT = bp->ft.T * (100.0+bp->ft.p) / 100.0; */

	/* scalar r = 1; */
		
    
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
			    
			myMRTEquilibrium( &mesh->lattice, mfields->T[nbid], mfields->U[nbid], lp->myMRT.alpha_1, lp->myMRT.alpha_2, f_eq_nb );
			    
			eq_nb  = f_eq_nb[k];


			/* // Equilibrium at boundary node */

			/* if(bp->ft.localTStep < bp->ft.psteps) { */

			/*     r = (scalar)rand() / RAND_MAX; */

			/*     scalar Tb = minT + (maxT-minT)*r; */

			/*     myMRTEquilibrium( &mesh->lattice, Tb, mfields->U[nbid], lp->myMRT.alpha_1, lp->myMRT.alpha_2, f_eq_nb ); */

			/* } */

			/* else { */

			    myMRTEquilibrium( &mesh->lattice, bp->ft.T, mfields->U[nbid], lp->myMRT.alpha_1, lp->myMRT.alpha_2, f_eq_nb );

			/* } */
			    
			eq_bnd = f_eq_nb[k];
			    

			
			// Update distribution
			
			field[id][k] = eq_bnd + (field[nbid][k] - eq_nb);

		    }
		

		}

	    }
	
	

	}


	free(f_eq_nb);

	/* bp->ft.localTStep++; */

    }
    




    else {

	errorMsg("Unable to apply boundary condition on temperature");

    }
           

}
