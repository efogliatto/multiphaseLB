/* #include <liMRTCollision.h> */
/* #include <stdlib.h> */
/* #include <matVecMult.h> */
/* #include <liMRTForce.h> */
/* #include <totalForce.h> */
/* #include <potential.h> */
/* #include <syncPdfField.h> */

/* #include <updateLambda.h> */


#include <basic.h>

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

#include <liMRTForce.h>


void liMRTCollision( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {


    // Indices
    
    unsigned int id, k;


    
    // Partial distributions
    
    double* m     = (double*)malloc( mesh->lattice.Q * sizeof(double) );   // m:  momentum space
    double* m_eq  = (double*)malloc( mesh->lattice.Q * sizeof(double) );   // meq: equilibrium in momentum space
    double* S     = (double*)malloc( mesh->lattice.Q * sizeof(double) );   // MRT force

    
    
    // Move over ALL points
    
    for( id = 0 ; id < mesh->mesh.nPoints ; id++ ) {
    /* for( id = 0 ; id < mesh->parallel.nlocal ; id++ ) { */
	

    	// Update Lambda values

	if( field->tauModel == 3 ) {

	    double a = (field->nb - field->na) / (field->rb - field->ra);

	    double b = field->na  -  a * field->ra;

	    double nu = a * mfields->rho[id] + b;

	    double tau = nu / mesh->lattice.cs2 + 0.5;

	    field->Lambda[7] = 1/tau;

	    field->Lambda[8] = 1/tau;

	}


	double umag = 0;
	
	for( k = 0 ; k < 3 ; k++ ) {
	
	    umag += mfields->U[id][k] * mfields->U[id][k];

	}

	
    	// Compute equilibrium in momentum space
	
    	m_eq[0] = mfields->rho[id];
    	m_eq[1] = mfields->rho[id] * (-2 + 3*umag);
    	m_eq[2] = mfields->rho[id] * (1 - 3*umag);
    	m_eq[3] = mfields->rho[id] * mfields->U[id][0];
    	m_eq[4] = mfields->rho[id] * (-mfields->U[id][0]);
    	m_eq[5] = mfields->rho[id] * mfields->U[id][1];
    	m_eq[6] = mfields->rho[id] * (-mfields->U[id][1]);
    	m_eq[7] = mfields->rho[id] * (mfields->U[id][0]*mfields->U[id][0] - mfields->U[id][1]*mfields->U[id][1]);
    	m_eq[8] = mfields->rho[id] * mfields->U[id][0] * mfields->U[id][1];

	

	
    	// Distribution in momentum space

    	matVecMult(mesh->lattice.M, field->value[id], m, mesh->lattice.Q);

	
    	// Total Force
	
    	liMRTForce( mesh, mfields, field, S, id );


	
    	// Collision in momentum space
	
    	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

    	    m[k] = m[k]  -  field->Lambda[k]*( m[k] - m_eq[k] )  +  ( 1 - 0.5*field->Lambda[k] ) * S[k];
	    
    	}

	
	
    	// Back to phase space
	
    	matVecMult(mesh->lattice.invM, m, field->value[id], mesh->lattice.Q);

	
    }


    // Deallocate memory
    free(m);
    free(m_eq);
    free(S);


    
}
