#include <stdio.h>
#include <stdlib.h>
#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>
#include <outflow.h>
#include <lbEquation.h>

void outflow( latticeMesh* mesh, macroFields* mfields, scalar** field, uint bid ) {


    uint i, j, k;

    scalar* f_eq_nb = (scalar*)malloc( mesh->mesh.Q * sizeof(scalar) );
	
    scalar* f_eq_bnd  = (scalar*)malloc( mesh->mesh.Q * sizeof(scalar) );


    

    // Move over boundary elements
    
    for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) {

	int id = mesh->mesh.bd.bdPoints[bid][i];


	// Check which is the normal direction, using unknown neighbours

	int normal[3] = {0,1,0};

	/* for( k = 0 ; k < mesh->mesh.Q ; k++ ) { */

	/*     if( mesh->mesh.nb[id][ mesh->lattice.reverse[k] ] == -1 ) { */

	/* 	for( j = 0 ; j < 3 ; j++ ) { */

	/* 	    normal[j] += mesh->lattice.vel[k][j]; */

	/* 	} */

	/*     } */

	/* } */

	/* for( j = 0 ; j < 3 ; j++ ) { */

	/*     if( normal[j] != 0 ) { */

	/* 	normal[j] = normal[j] / abs(normal[j]); */

	/*     } */

	/* } */

	/* printf("%d %d %d\n",normal[0],normal[1],normal[2]); */
	


	// Detect correspondence with lattice velocities

	uint ln = 0;

	for( k = 0 ; k < mesh->mesh.Q ; k++ ) {
	    
	    if(  (mesh->lattice.vel[k][0] == normal[0])  &&  (mesh->lattice.vel[k][1] == normal[1])  &&  (mesh->lattice.vel[k][2] == normal[2])  ) {
		
	    	ln = k;

	    }

	}
	
	

	// Interpolate missing components from neighbour in normal direction

	uint neigh = mesh->mesh.nb[id][ln];

	if( neigh != -1 ) {

	    scalar uAdv = 0;


	    // Compute local velocity at t+dt (macro fields are not updated yet)

	    // Local velocity
	    scalar lv[3] = {0,0,0};

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

			lv[jj] += mesh->lattice.vel[kk][jj] * field[neigh][kk];
		    
		    }
	    
		}


		for(kk = 0 ; kk < mesh->mesh.Q ; kk++) {

		    nbrho += field[neigh][kk];

		    lrho += field[id][kk];

		}
		

		// Add interaction force and divide by density
		for( jj = 0 ; jj < 3 ; jj++ ) {

		    lv[jj] = ( lv[jj]   +   F[jj] * 0.5  ) / nbrho;
	
		}


		for( jj = 0 ; jj < 3 ; jj++ ) {

		    uAdv += normal[jj] * lv[jj];
	
		}		

		

	    }



	    
	    /* for( j = 0 ; j < 3 ; j++ ) { */

	    /* 	mfields->U[id][j] = (mfields->rho[id]*mfields->U[id][j] + uAdv*nbrho*lv[j]) / ((1+uAdv)*lrho); */

	    /* } */


	    
	    for( k = 0 ; k < mesh->mesh.Q ; k++ ) {

	    	/* if( mesh->mesh.nb[id][k] == -1 ) { */
		
	    	    field[id][k] = (  field[id][k] + uAdv*field[neigh][k]  ) / (1+uAdv);

	    	/* } */

	    }

	    /* printf("%g\n",uAdv); */
	    

	}
	

	

    }



    free(f_eq_nb);

    free(f_eq_bnd);

}
