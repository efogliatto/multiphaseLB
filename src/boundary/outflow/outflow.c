#include <stdio.h>
#include <stdlib.h>
#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>
#include <outflow.h>
#include <lbEquation.h>
#include <math.h>
#include <basic.h>


void outflow( latticeMesh* mesh, macroFields* mfields, scalar** field, uint bid ) {


    uint i, j, k;

    scalar* f_eq_nb = (scalar*)malloc( mesh->mesh.Q * sizeof(scalar) );
	
    scalar* f_eq_bnd  = (scalar*)malloc( mesh->mesh.Q * sizeof(scalar) );


    

    // Move over boundary elements
    
    for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) {

	int id = mesh->mesh.bd.bdPoints[bid][i];


	// Check which is the normal direction, using unknown neighbours

	float normal[3] = {0,0,0};

	for( k = 0 ; k < mesh->mesh.Q ; k++ ) {

	    if( mesh->mesh.nb[id][ mesh->lattice.reverse[k] ] == -1 ) {

		for( j = 0 ; j < 3 ; j++ ) {

		    normal[j] += mesh->lattice.vel[k][j];

		}

	    }

	}

	float nmag = 0;

	for( j = 0 ; j < 3 ; j++ ) {

	    nmag += normal[j] * normal[j];
	    
	}


	if( nmag!=0 ) {

	    nmag = sqrt(nmag);

	    for( j = 0 ; j < 3 ; j++ ) {

		normal[j] = normal[j] / nmag;

	    }
	    
	}

	else {

	    errorMsg("Unable to detect normal in outflow boundary");

	}

       
	


	// Detect correspondence with lattice velocities

	uint ln = 0;

	for( k = 0 ; k < mesh->mesh.Q ; k++ ) {
	    
	    if(      (mesh->lattice.vel[k][0] == (int)normal[0])
		 &&  (mesh->lattice.vel[k][1] == (int)normal[1])
		 &&  (mesh->lattice.vel[k][2] == (int)normal[2])  ) {
		
	    	ln = k;

	    }

	}
	


	

	// Interpolate missing components from neighbour in normal direction

	uint neigh = mesh->mesh.nb[id][ln];

	if( neigh != -1 ) {

	    scalar uAdv = 0;


	    // Compute local velocity at t+dt (macro fields are not updated yet)

	    // Local velocity
	    scalar nbv[3] = {0,0,0};

	    // Local density
	    scalar nbrho = 0;

	    scalar lrho = 0;
	    
	    #warning "Outflow velocity is not general"
	    
	    {

		uint jj, kk;

		// Interaction force
		scalar F[3];

	
		// Compute Total force
	
		for( jj = 0 ; jj < 3 ; jj++ ) {

		    F[jj] = mfields->Fi[neigh][jj]  +   (mfields->rho[neigh] - mesh->EOS.rho_0) * mesh->EOS.g[jj];

		}          


		// Move over velocity components
		for( jj = 0 ; jj < 3 ; jj++ ) {

		    // Move over model velocities
		    for(kk = 0 ; kk < mesh->mesh.Q ; kk++) {

			nbv[jj] += mesh->lattice.vel[kk][jj] * field[neigh][kk];
		    
		    }
	    
		}


		for(kk = 0 ; kk < mesh->mesh.Q ; kk++) {

		    nbrho += field[neigh][kk];

		    lrho += field[id][kk];

		}
		

		// Add interaction force and divide by density
		for( jj = 0 ; jj < 3 ; jj++ ) {

		    nbv[jj] = ( nbv[jj]   +   F[jj] * 0.5  ) / nbrho;
	
		}


		for( jj = 0 ; jj < 3 ; jj++ ) {

		    uAdv += normal[jj] * nbv[jj];
	
		}		

		

	    }



	    // Update unknowun distributions for f
	    
	    for( k = 0 ; k < mesh->mesh.Q ; k++ ) {

	    	if( mesh->mesh.nb[id][k] == -1 ) {
		
	    	    field[id][k] = (  field[id][k] + uAdv*field[neigh][k]  ) / (1+uAdv);

	    	}

	    }

	    /* printf("%g\n",uAdv); */
	    

	}
	

	

    }



    free(f_eq_nb);

    free(f_eq_bnd);

}
