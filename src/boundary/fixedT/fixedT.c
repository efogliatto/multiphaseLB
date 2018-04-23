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


void fixedT( latticeMesh* mesh, macroFields* mfields, double** field, unsigned int bid, lbeModel model, bdParam* bp, lbParameters* lp ) {



    // Apply only if collision model is myMRT
   
    if( model == myMRT ) {

	
	unsigned int i, k;

	double* f_eq_nb = (double*)malloc( mesh->mesh.Q * sizeof(double) );

	double eq_bnd = 0;
	
	double eq_nb = 0;
		
    
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


			// Equilibrium at boundary node

			myMRTEquilibrium( &mesh->lattice, bp->ft.T, mfields->U[nbid], lp->myMRT.alpha_1, lp->myMRT.alpha_2, f_eq_nb );
			    
			eq_bnd = f_eq_nb[k];
			    

			
			// Update distribution
			
			field[id][k] = eq_bnd + (field[nbid][k] - eq_nb);

		    }
		

		}

	    }
	
	

	}


	free(f_eq_nb);


    	}



    	else {

    	    errorMsg("Unable to apply boundary condition on temperature");

    	}
           

}








    /* // Apply only if collision model is liTemp */

    /* if(  ( field->colId == 2 )  ||  ( field->colId == 3 )  ){ */

	
    /* 	unsigned int i, k; */

    /* 	double* f_eq_nb = (double*)malloc( mesh->mesh.Q * sizeof(double) ); */

    /* 	double eq_bnd = 0; */
	
    /* 	double eq_nb = 0; */

	
    /* 	srand( time(NULL) ); */
	
    
    /* 	// Move over boundary elements */

    /* 	for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) { */

	
    /* 	    unsigned int id = mesh->mesh.bd.bdPoints[bid][i]; */

	
	
    /* 	    // Move over lattice velocities */
	    
    /* 	    for( k = 0 ; k < mesh->mesh.Q ; k++ ) { */


    /* 		if ( mesh->mesh.nb[id][k] == -1 ) { */


    /* 		    // Need density and velocity at neighbour (reverse) node */
		    
    /* 		    int nbid = mesh->mesh.nb[id][ mesh->lattice.reverse[k] ];		     */
		    
    /* 		    if( nbid != -1 ) { */

    /* 			liTempEquilibrium( &mesh->lattice, mfields->rho[nbid], mfields->U[nbid], f_eq_nb ); */



			
    /* 			// Use perturbations */

    /* 			double r = 1; */
			
    /* 			if( field->boundary[bid].vectorVal[0] != 0 ) { */

    /* 			    r = (double)rand() / (double)RAND_MAX; */

    /* 			    r = (1.0 - field->boundary[bid].vectorVal[0]/100) + r * ( (1.0 + field->boundary[bid].vectorVal[0]/100) - (1.0 - field->boundary[bid].vectorVal[0]/100) ); */
    /* 			} */

			
    /* 			eq_bnd = mesh->EOS._Cv * field->boundary[bid].scalarVal * r * f_eq_nb[k]; */
			    
    /* 			eq_nb  = mesh->EOS._Cv * singleNodeT(mesh, mfields, field, nbid) * f_eq_nb[k]; */




			
    /* 			// Update distribution */
			
    /* 			field->value[id][k] = eq_bnd + (field->value[nbid][k] - eq_nb); */

    /* 		    } */


    /* 		    /\* else { *\/ */

    /* 		    /\* 	noneigh++; *\/ */

    /* 		    /\* } *\/ */
		

    /* 		} */

    /* 	    } */




    /* 	    /\* // Apply correction for corners *\/ */
    /* 	    /\* if( noneigh != 0 ) { *\/ */

	    
    /* 	    /\* } *\/ */




	
	

    /* 	} */


    /* 	free(f_eq_nb); */


    /* } */