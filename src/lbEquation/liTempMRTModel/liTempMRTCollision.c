#include <basic.h>
#include <liTempMRTCollision.h>
#include <liTempMRTSource.h>
#include <liTempMRTEquilibriumMS.h>



void liTempMRTCollision( latticeMesh* mesh, macroFields* mfields, lbeField* field ) {


    // Indices
    
    uint id, k;


    
    // Partial distributions
    
    scalar* n     = (scalar*)malloc( mesh->lattice.Q * sizeof(scalar) );   // m:  momentum space
    
    scalar* n_eq  = (scalar*)malloc( mesh->lattice.Q * sizeof(scalar) );   // meq: equilibrium in momentum space   
    
    scalar* GammaHat = (scalar*)malloc( mesh->lattice.Q * sizeof(scalar) );   // Source in population space
    
     

    
    
    // Move over ALL points
    
    for( id = 0 ; id < mesh->mesh.nPoints ; id++ ) {
    /* for( id = 0 ; id < mesh->parallel.nlocal ; id++ ) { */

	

	// Equilibrium distribution in moment space

	liTempMRTEquilibriumMS( mesh, mfields, n_eq, id );
	
	
	
    	// Distribution in momentum space

    	matVecMult(mesh->lattice.M, field->value[id], n, mesh->lattice.Q);



	// Source in momentum space (heat sink, compression work and correction terms)

	liTempMRTSource(mesh, mfields, field, GammaHat, id);       
	
	
	
	
    	// Collision in momentum space

	scalar n4 = n[4],
	    n6 = n[6];
	
    	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

    	    n[k] = n[k] - field->lbparam.liTempMRT.Lambda[k] * (n[k] - n_eq[k]) + GammaHat[k];
	    
    	}


	

	// Explicit element correction

	n[3] = n[3] + (1 - field->lbparam.liTempMRT.Lambda[3]/2) * field->lbparam.liTempMRT.Lambda[4] * (n4 - n_eq[4]);

	n[5] = n[5] + (1 - field->lbparam.liTempMRT.Lambda[5]/2) * field->lbparam.liTempMRT.Lambda[6] * (n6 - n_eq[6]);
	

	
	
    	// Back to population space
	
    	matVecMult(mesh->lattice.invM, n, field->value[id], mesh->lattice.Q);

	
    }

    

    // Deallocate memory

    free(n);

    free(n_eq);

    free(GammaHat);

    

    
}
