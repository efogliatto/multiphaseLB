#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>
#include <newTempEquilibrium.h>
#include <stdlib.h>
#include <pseudoPot.h>



void newTempCollision( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {


    // Indices
    unsigned int id, k, j;
    
    // Dot product for correction term    
    double kappa, dot, M;

    // Interaction force
    double F[3];
    
    // Partial distributions
    double* f_eq = (double*)malloc( mesh->lattice.Q * sizeof(double) );


    
    // Move over ALL points
    
    /* for( id = 0 ; id < mesh->parallel.nlocal ; id++ ) { */
    for( id = 0 ; id < mesh->mesh.nPoints ; id++ ) {

	
	// Update real tau

	// Constant Lambda
	
	if( field->tauModel == 2 ) {
	
	    field->tau = 0.5 + field->lambda / (mesh->lattice.cs2 * mfields->rho[id] * mesh->EOS._Cv);

	}

	else {

	    if( field->tauModel == 4 ) {

		double a = (field->nb - field->na) / (field->rb - field->ra);

		double b = field->na  -  a * field->ra;

		double lambda = a * mfields->rho[id] + b;

		field->tau = 0.5 + lambda / (mesh->lattice.cs2 * mfields->rho[id] * mesh->EOS._Cv);

	    }

	}

	
	// Compute momentum equilibrium
	newTempEquilibrium(&mesh->lattice, mfields->rho[id], mfields->U[id], f_eq);	

		

	unsigned int jj;
	
	for( jj = 0 ; jj < 3 ; jj++ ) {

	    F[jj] = mfields->Fi[id][jj]  +   (mfields->rho[id] - mesh->EOS.rho_0) * mesh->EOS._g[jj];

	}


	

	
	
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


	    

	    // Compresion work
	    
	    dot = 0;
	    
	    for( j = 0 ; j < 3 ; j++) {
		
	    	dot += mesh->lattice.vel[k][j] * mfields->U[id][j];
		
	    }

	    M = M   +   ( 1 - 0.5 / field->tau) * mfields->phiDivU[id] * mesh->lattice.omega[k] * dot / mesh->lattice.cs2;



	    
	    /* // Wrong */
	    
	    /* M = M - phi * mesh->lattice.omega[k] * dot / (mesh->lattice.cs2 * field->tau); */


	    

	    
	    
	    // Collision

	    
	    field->value[id][k] =
		field->value[id][k]  -
		(  field->value[id][k]  -  mesh->EOS._Cv * mfields->T[id] * f_eq[k]  ) / field->tau   +
		M +
		( 1 - 0.5 / field->tau) * mfields->phiDivU[id] * mesh->lattice.omega[k] ;

	    
	}


    }


    // Deallocate memory
    free(f_eq);


}
