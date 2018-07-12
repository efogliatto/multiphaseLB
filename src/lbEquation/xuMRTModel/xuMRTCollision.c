#include <basic.h>
#include <xuMRTCollision.h>
#include <xuMRTForce.h>
#include <xuMRTSurfaceTension.h>


void xuMRTCollision( latticeMesh* mesh, macroFields* mfields, lbeField* field ) {


    // Indices
    
    uint id, k;


    
    // Partial distributions
    
    scalar* m     = (scalar*)malloc( mesh->lattice.Q * sizeof(scalar) );   // m:  momentum space
    
    scalar* m_eq  = (scalar*)malloc( mesh->lattice.Q * sizeof(scalar) );   // meq: equilibrium in momentum space

    scalar* S     = (scalar*)malloc( mesh->lattice.Q * sizeof(scalar) );   // MRT force

    scalar* C     = (scalar*)malloc( mesh->lattice.Q * sizeof(scalar) );   // Surface tension term





    // Depending on surface tension model, computes collision over all points, or only local.
    // If only local, syncs field at the end

    uint nodes = mesh->mesh.nPoints;

    if( field->lbparam.xuMRT.surfaceTension == xuSurfTen ) {

	nodes = mesh->parallel.nlocal;

    }
    

    
    for( id = 0 ; id < nodes ; id++ ) {
	


	scalar U[3] = { mfields->U[id][0], mfields->U[id][1], mfields->U[id][2] };

	scalar rho = mfields->rho[id];
	
	scalar umag = vectorMag2(U);

		

	
	// Compute equilibrium in momentum space
	
	m_eq[0]  = rho;
	
	m_eq[1]  = rho * (-1.0 + umag);

	m_eq[2]  = rho * (1.0 - 5.0*umag);

	m_eq[3]  = rho * U[0];

	m_eq[4]  = rho * -7.0 * U[0] / 3.0;

	m_eq[5]  = rho * U[1];

	m_eq[6]  = rho * -7.0 * U[1] / 3.0;

	m_eq[7]  = rho * U[2];

	m_eq[8]  = rho * -7.0 * U[2] / 3.0;

	m_eq[9]  = rho * 2.0 * U[0] * U[0]  -  U[1] * U[1]  -  U[2] * U[2];

	m_eq[10] = rho * U[1] * U[1]  -  U[2] * U[2];

	m_eq[11] = rho * U[0]*U[1];

	m_eq[12] = rho * U[1]*U[2];

	m_eq[13] = rho * U[0]*U[2];

	m_eq[14] = rho * 0;

	

	
	// Distribution in momentum space

	matVecMult(mesh->lattice.M, field->value[id], m, mesh->lattice.Q);
	

	
	// Total Force
	
	xuMRTForce( mesh, mfields, field, S, id );


	
	// Surface Tension term
	
	xuMRTSurfaceTension( mesh, mfields, field, C, id );
	

	
	// Collision in momentum space
	
	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

	    m[k] = m[k]  -  field->lbparam.xuMRT.Lambda[k]*( m[k] - m_eq[k] )  +  ( 1 - 0.5*field->lbparam.xuMRT.Lambda[k] ) * S[k];

	    if(field->lbparam.xuMRT.surfaceTension == xuSurfTen) {

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

    if( field->lbparam.xuMRT.surfaceTension == xuSurfTen ) {

	syncPdfField( mesh, field->value );

    }    


    
}
