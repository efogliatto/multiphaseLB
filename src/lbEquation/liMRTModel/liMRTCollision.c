#include <basic.h>
#include <liMRTCollision.h>
#include <liMRTForce.h>
#include <liMRTSurfaceTension.h>


void liMRTCollision( latticeMesh* mesh, macroFields* mfields, lbeField* field ) {


    // Indices
    
    unsigned int id, k;


    
    // Partial distributions
    
    double* m     = (double*)malloc( mesh->lattice.Q * sizeof(double) );   // m:  momentum space
    
    double* m_eq  = (double*)malloc( mesh->lattice.Q * sizeof(double) );   // meq: equilibrium in momentum space

    double* S     = (double*)malloc( mesh->lattice.Q * sizeof(double) );   // MRT force

    double* C     = (double*)malloc( mesh->lattice.Q * sizeof(double) );   // Surface tension term




    // Depending on surface tension model, computes collision over all points, or only local.
    // If only local, syncs field at the end

    unsigned int nodes = mesh->mesh.nPoints;

    if( field->lbparam.liMRT.surfaceTension == liSurfTen ) {

	nodes = mesh->parallel.nlocal;

    }
    

    
    for( id = 0 ; id < nodes ; id++ ) {
	



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


	
	// Surface Tension term
	
	liMRTSurfaceTension( mesh, mfields, field, C, id );
	

	
	// Collision in momentum space
	
	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

	    m[k] = m[k]  -  field->lbparam.liMRT.Lambda[k]*( m[k] - m_eq[k] )  +  ( 1 - 0.5*field->lbparam.liMRT.Lambda[k] ) * S[k];

	    if(field->lbparam.liMRT.surfaceTension == liSurfTen) {

	    	m[k] = m[k] + C[k];

	    }
	    
	}

	
	
	// Back to phase space
	
	matVecMult(mesh->lattice.invM, m, field->value[id], mesh->lattice.Q);

	
    }


    // Deallocate memory

    free(m);
    
    free(m_eq);

    free(S);

    free(C);


    
    // Sync field if needed

    if( field->lbparam.liMRT.surfaceTension == liSurfTen ) {

	syncPdfField( mesh, field->value );

    }    


    
}
