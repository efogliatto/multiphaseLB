#include <stdio.h>
#include <stdlib.h>
#include <fixedU.h>
#include <liMRTEquilibrium.h>


void fixedU( latticeMesh* mesh, macroFields* mfields, scalar** field, uint bid, lbeModel model, bdParam* bp, lbParameters* lp ) {


    if( model == liMRT ) {

	
	unsigned int i, k;

	scalar* f_eq_nb = (scalar*)malloc( mesh->mesh.Q * sizeof(scalar) );

	scalar* f_eq_bnd  = (scalar*)malloc( mesh->mesh.Q * sizeof(scalar) );
	

    
	// Velocity at boundary

	scalar Uw[3];
	Uw[0] = bp->fu.U[0];
	Uw[1] = bp->fu.U[1];
	Uw[2] = bp->fu.U[2];
    
    
	// Move over boundary elements

	for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) {

	
	    uint id = mesh->mesh.bd.bdPoints[bid][i];
	
	
	    // Move over lattice velocities
	    
	    for( k = 0 ; k < mesh->mesh.Q ; k++ ) {


		if ( mesh->mesh.nb[id][k] == -1 ) {

		
		    // Need density and velocity at neighbour (reverse) node
		    
		    int nbid = mesh->mesh.nb[id][ mesh->lattice.reverse[k] ];


		    if( nbid != -1 ) {


			// Compute local velocity at t+dt (macro fields are not updated yet)

			// Local velocity
			scalar lv[3] = {0,0,0};

			// Local density
			scalar nbrho = 0;

			scalar lrho = 0;
			
	    
			{

			    uint jj, kk;

			    // Interaction force
			    scalar F[3];

	
			    // Compute Total force
	
			    for( jj = 0 ; jj < 3 ; jj++ ) {

				F[jj] = mfields->Fi[nbid][jj]  +   (mfields->rho[bid] - mesh->EOS.rho_0) * mesh->EOS.g[jj];

			    }          


			    // Move over velocity components
			    for( jj = 0 ; jj < 3 ; jj++ ) {

				// Move over model velocities
				for(kk = 0 ; kk < mesh->mesh.Q ; kk++) {

				    lv[jj] += mesh->lattice.vel[kk][jj] * field[nbid][kk];
		    
				}
	    
			    }


			    for(kk = 0 ; kk < mesh->mesh.Q ; kk++) {

				nbrho += field[nbid][kk];

				lrho += field[id][kk];

			    }
		

			    // Add interaction force and divide by density
			    for( jj = 0 ; jj < 3 ; jj++ ) {

				lv[jj] = ( lv[jj]   +   F[jj] * 0.5  ) / nbrho;
	
			    }

			}

			
			

			/* liMRTEquilibrium( &mesh->lattice, mfields->rho[nbid], mfields->U[nbid], f_eq_nb ); */
			liMRTEquilibrium( &mesh->lattice, nbrho, lv, f_eq_nb );

			liMRTEquilibrium( &mesh->lattice, nbrho, Uw, f_eq_bnd );

			
		    

			// Update distribution
			
			field[id][k] = f_eq_bnd[k] + (field[nbid][k] - f_eq_nb[k] );

		    }
		

		}

	    }

	}


	free(f_eq_nb);

	free(f_eq_bnd);
	

    }

}
