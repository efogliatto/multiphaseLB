#include <basic.h>

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

#include <myMRTSource.h>


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


	double umag = 0;
	
	for( k = 0 ; k < 3 ; k++ ) {
	
	    umag += mfields->U[id][k] * mfields->U[id][k];

	}

	
    	// Compute equilibrium in momentum space
	
    	n_eq[0] = mfields->T[id] * mesh->EOS._Cv * mfields->rho[id];
    	n_eq[1] = mfields->T[id] * mesh->EOS._Cv * mfields->rho[id] * (-2 + 3*umag);
    	n_eq[2] = mfields->T[id] * mesh->EOS._Cv * mfields->rho[id] * (1 - 3*umag);
    	n_eq[3] = mfields->T[id] * mesh->EOS._Cv * mfields->rho[id] * mfields->U[id][0];
    	n_eq[4] = mfields->T[id] * mesh->EOS._Cv * mfields->rho[id] * (-mfields->U[id][0]);
    	n_eq[5] = mfields->T[id] * mesh->EOS._Cv * mfields->rho[id] * mfields->U[id][1];
    	n_eq[6] = mfields->T[id] * mesh->EOS._Cv * mfields->rho[id] * (-mfields->U[id][1]);
    	n_eq[7] = mfields->T[id] * mesh->EOS._Cv * mfields->rho[id] * (mfields->U[id][0]*mfields->U[id][0] - mfields->U[id][1]*mfields->U[id][1]);
    	n_eq[8] = mfields->T[id] * mesh->EOS._Cv * mfields->rho[id] * mfields->U[id][0] * mfields->U[id][1];

	

	
    	// Distribution in momentum space

    	matVecMult(mesh->lattice.M, field->value[id], n, mesh->lattice.Q);


	// Source in population space (heat sink, compression work and correction terms)

	myMRTSource(mesh, mfields, Gamma, id);


	// Source in momentum space

	matVecMult(mesh->lattice.M, Gamma, GammaHat, mesh->lattice.Q);

	
	
    	// Collision in momentum space
	
    	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

    	    m[k] = m[k]  -  field->Lambda[k]*( m[k] - m_eq[k] )  +  ( 1 - 0.5*field->Lambda[k] ) * S[k];
	    
    	}

	
	
    	/* // Back to phase space */
	
    	/* matVecMult(mesh->lattice.invM, m, field->value[id], mesh->lattice.Q); */

	
    }


    // Deallocate memory
    free(n);
    free(n_eq);
    free(Gamma);


    
}
