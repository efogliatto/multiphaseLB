#include <liTempMRTEquilibriumMS.h>
#include <basic.h>

void liTempMRTEquilibriumMS( latticeMesh* mesh, macroFields* mfields, scalar* n_eq, uint id ) {


    // Cache variables
    
    scalar T = mfields->T[id];

    scalar U[3] = {mfields->U[id][0], mfields->U[id][1], mfields->U[id][2]};

    
    
    // Compute equilibrium in momentum space
    
    switch( mesh->lattice.model ) {


    case D2Q9:

	n_eq[0] = T;
	
    	n_eq[1] = -2.0 * T;
	
    	n_eq[2] = 2.0 * T;
	
    	n_eq[3] = T * U[0];
	
    	n_eq[4] = T * (-U[0]);
	
    	n_eq[5] = T * U[1];
	
    	n_eq[6] = T * (-U[1]);
	
    	n_eq[7] = 0;
	
    	n_eq[8] = 0;

	
	break;


	
    default:

	errorMsg("Lattice model not available for liTempMRTModel");

	break;

    }



}
