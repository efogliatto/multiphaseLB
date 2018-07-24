#include <basic.h>
#include <xuMRTCollision.h>
#include <xuMRTForce.h>
#include <xuMRTSurfaceTension.h>
#include <xuMRTEquilibriumMS.h>


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
			

	
	// Compute equilibrium in momentum space
	
	xuMRTEquilibriumMS( mesh, mfields, m_eq, id );

	

	
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
