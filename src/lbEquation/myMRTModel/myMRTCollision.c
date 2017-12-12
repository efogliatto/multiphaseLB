#include <basic.h>

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

#include <myMRTSource.h>
#include <myMRTEquilibriumMS.h>


void myMRTCollision( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {


    // Indices
    
    unsigned int id, k;


    
    // Partial distributions
    
    double* n     = (double*)malloc( mesh->lattice.Q * sizeof(double) );   // m:  momentum space
    
    double* n_eq  = (double*)malloc( mesh->lattice.Q * sizeof(double) );   // meq: equilibrium in momentum space
    
    double* Gamma = (double*)malloc( mesh->lattice.Q * sizeof(double) );   // Source in population space
    
    double* GammaHat = (double*)malloc( mesh->lattice.Q * sizeof(double) );   // Source in population space

    
    
    // Move over ALL points
    
    for( id = 0 ; id < mesh->mesh.nPoints ; id++ ) {
    /* for( id = 0 ; id < mesh->parallel.nlocal ; id++ ) { */
	

    	/* // Update Lambda values */

	/* if( field->tauModel == 3 ) { */

	/*     double a = (field->nb - field->na) / (field->rb - field->ra); */

	/*     double b = field->na  -  a * field->ra; */

	/*     double nu = a * mfields->rho[id] + b; */

	/*     double tau = nu / mesh->lattice.cs2 + 0.5; */

	/*     field->Lambda[7] = 1/tau; */
	
	/*     field->Lambda[8] = 1/tau; */

	/* } */

	

	// Equilibrium distribution in moment space

	myMRTEquilibriumMS( mesh, mfields, n_eq, id );
	
	
    	// Distribution in momentum space

    	matVecMult(mesh->lattice.M, field->value[id], n, mesh->lattice.Q);


	// Source in population space (heat sink, compression work and correction terms)

	myMRTSource(mesh, mfields, Gamma, id);


	// Source in momentum space

	matVecMult(mesh->lattice.M, Gamma, GammaHat, mesh->lattice.Q);

	
	
    	// Collision in momentum space
	
    	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

    	    n[k] = n[k]  -  field->Lambda[k]*( n[k] - n_eq[k] )  +  ( 1 - 0.5*field->Lambda[k] ) * GammaHat[k];
	    
    	}

	
	
    	// Back to population space
	
    	matVecMult(mesh->lattice.invM, n, field->value[id], mesh->lattice.Q);

	
    }

    

    // Deallocate memory

    free(n);

    free(n_eq);

    free(Gamma);


    
}
