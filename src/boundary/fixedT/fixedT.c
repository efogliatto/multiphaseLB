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


void fixedT( latticeMesh* mesh, macroFields* mfields, double** field, unsigned int bid, lbeModel model, bdParam* bp, lbParameters* lp ) {



    // Apply only if collision model is myMRT
   
    if( model == myMRT ) {

	
	unsigned int i, k;

	double* f_eq_nb = (double*)malloc( mesh->mesh.Q * sizeof(double) );

	double eq_bnd = 0;
	
	double eq_nb = 0;



	/* // Perturbation conditions */

	/* srand(0); */

	/* double minT = bp->ft.T * (100.0-bp->ft.p) / 100.0; */

	/* double maxT = bp->ft.T * (100.0+bp->ft.p) / 100.0; */

	/* double r = 1; */
		
    
	// Move over boundary elements

	for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) {

	
	    unsigned int id = mesh->mesh.bd.bdPoints[bid][i];

	
	
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

			/*     r = (double)rand() / RAND_MAX; */

			/*     double Tb = minT + (maxT-minT)*r; */

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
