#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>
#include <liTempEquilibrium.h>
#include <stdlib.h>
#include <pseudoPot.h>


void liTempCollision( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {


    // Indices
    unsigned int id, k, j;
    
    // Dot product for correction term    
    double kappa, dot, M;//, phi;

    // Interaction force
    double F[3];
    
    // Partial distributions
    double* f_eq = (double*)malloc( mesh->lattice.Q * sizeof(double) );


    
    // Move over points
    
    for( id = 0 ; id < mesh->parallel.nlocal ; id++ ) {


	// Update real tau

	// Constant Lambda
	
	if( field->tauModel == 2 ) {
	
	    field->tau = 0.5 + field->lambda / (mesh->lattice.cs2 * mfields->rho[id] * mesh->EOS._Cv);

	}

	
	// Compute momentum equilibrium
	liTempEquilibrium(&mesh->lattice, mfields->rho[id], mfields->U[id], f_eq);	

		
	// Interaction force
	totalForce( mesh, F, mfields->rho, mfields->T, id);


	
	/* // Parameter for compression work */
	/* phi = -mfields->T[id] * (p_eos(&mesh->EOS, mfields->rho[id], mfields->T[id]*1.1) - p_eos(&mesh->EOS, mfields->rho[id], mfields->T[id]*0.9)) / ( 2 * mfields->T[id]); */



	
	// Collide g
	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {


	    M = 0;
	    
	    // Correction term (force)
	    kappa = ( 1 - 0.5 / field->tau) * mesh->lattice.omega[k] * mesh->EOS._Cv * mfields->T[id] / mesh->lattice.cs2;
	    
	    dot = 0;
	    
	    for( j = 0 ; j < 3 ; j++) {
		
	    	dot += mesh->lattice.vel[k][j] * F[j];
		
	    }

	    M = kappa * dot;


	    

	    /* // Compresion work */
	    
	    /* dot = 0; */
	    /* for( j = 0 ; j < 3 ; j++) { */
	    /* 	dot += mesh->lattice.c * mesh->lattice.vel[k][j] * mfields->U[id][j]; */
	    /* } */

	    /* M = M - phi * mesh->lattice.omega[k] * dot / (field->tau * mesh->time.tstep * mesh->lattice.cs2); */


	    
	    
	    // Collision
	    field->value[id][k] = field->value[id][k]  -
		       (  field->value[id][k]  -  mesh->EOS._Cv * mfields->T[id] * f_eq[k]  ) / field->tau   +
		        M;

	    
	}


    }


    // Deallocate memory
    free(f_eq);


    /* // Synchronize field */
    /* syncPdfField( &mesh->parallel, field->value, mesh->lattice.Q ); */

}
