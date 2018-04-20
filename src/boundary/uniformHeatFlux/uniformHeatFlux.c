#include <stdio.h>
#include <stdlib.h>
#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>
#include <liTempEquilibrium.h>
#include <myMRTEquilibrium.h>
#include <singleNodeT.h>


void uniformHeatFlux(  latticeMesh* mesh,  macroFields* mfields,  double** field, unsigned int bid ) {


    // Apply only if collision model is liTemp or myMRTModel

    if(  ( field->colId == 2 ) ||  ( field->colId == 4 )  ){

	
	unsigned int i, k;

	double* f_eq_nb = (double*)malloc( mesh->mesh.Q * sizeof(double) );

	double eq_bnd = 0;
	
	double eq_nb = 0;

	
	
    
	// Move over boundary elements

	for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) {

	
	    unsigned int id = mesh->mesh.bd.bdPoints[bid][i];


	    // Compute thermal conductivity

	    double lambda = 0;

	    if( field->colId == 2 ) {

		lambda = ( field->tau - 0.5 ) * mfields->rho[id] * mesh->lattice.cs2 * mesh->EOS._Cv;

	    }

	    else {

		if( field->colId == 4 ) {

		    lambda = mfields->rho[id] * mesh->EOS._Cv * (1/field->Lambda[3] - 0.5) * (4.0 + 3.0 * field->alpha_1 + 2.0 * field->alpha_2) / 6.0;

		}

	    }

	    



	    // Move over lattice velocities. Check direction


	    // Estimated boundary temperature
	    
	    double t_bd = 0;
	    
	    for( k = 0 ; k < mesh->mesh.Q ; k++ ) {

		if(   ( (int)field->boundary[bid].vectorVal[0] == mesh->lattice.vel[k][0] )  &&
		      ( (int)field->boundary[bid].vectorVal[1] == mesh->lattice.vel[k][1] )  &&
		      ( (int)field->boundary[bid].vectorVal[2] == mesh->lattice.vel[k][2] )     ) {


		    // Compute temperature value using neighbour information
		    int nbid = mesh->mesh.nb[id][ mesh->lattice.reverse[k] ];

		    if( nbid != -1 ) {

			t_bd = singleNodeT(mesh, mfields, field, nbid) + field->boundary[bid].scalarVal / lambda;

		    }

		    else {

			nbid = mesh->mesh.nb[id][k];

			t_bd = singleNodeT(mesh, mfields, field, nbid) - field->boundary[bid].scalarVal / lambda;

		    }



		}
		
	    }


	    if( field->colId == 2 ) {
	
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



	    else {

		
		// Move over lattice velocities
	    
		for( k = 0 ; k < mesh->mesh.Q ; k++ ) {


		    if ( mesh->mesh.nb[id][k] == -1 ) {


			// Need density and velocity at neighbour (reverse) node
		    
			int nbid = mesh->mesh.nb[id][ mesh->lattice.reverse[k] ];		    
		    
			if( nbid != -1 ) {

			    
			    // Equilibrium at neighbour node
			    
			    myMRTEquilibrium( &mesh->lattice, mfields->T[nbid], mfields->U[nbid], field->alpha_1, field->alpha_2, f_eq_nb );
			    
			    eq_nb  = f_eq_nb[k];


			    // Equilibrium at boundary node

			    myMRTEquilibrium( &mesh->lattice, t_bd, mfields->U[nbid], field->alpha_1, field->alpha_2, f_eq_nb );
			    
			    eq_bnd = f_eq_nb[k];
			    

			
			    // Update distribution
			
			    field->value[id][k] = eq_bnd + (field->value[nbid][k] - eq_nb);

			}
		

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
