#include <myMRTEquilibriumMS.h>
#include <basic.h>

void myMRTEquilibriumMS( latticeMesh* mesh, macroFields* mfields, scalar* n_eq, scalar alpha_1, scalar alpha_2, uint id ) {


    // Cache variables
    
    scalar T = mfields->T[id];

    scalar U[3] = {mfields->U[id][0], mfields->U[id][1], mfields->U[id][2]};

    
    
    // Compute equilibrium in momentum space
    
    switch( mesh->lattice.model ) {


    case D2Q9:

	n_eq[0] = T;
	
    	n_eq[1] = alpha_1 * T;
	
    	n_eq[2] = alpha_2 * T;
	
    	n_eq[3] = T * U[0];
	
    	n_eq[4] = T * (-U[0]);
	
    	n_eq[5] = T * U[1];
	
    	n_eq[6] = T * (-U[1]);
	
    	n_eq[7] = 0;
	
    	n_eq[8] = 0;

	
	break;



    case D3Q15:

	n_eq[0]  = T;
	
	n_eq[1]  = alpha_1 * T;

	n_eq[2]  = alpha_2 * T;

	n_eq[3]  =   T * U[0];

	n_eq[4]  = -(T * U[0]);

	n_eq[5]  =   T * U[1];

	n_eq[6]  = -(T * U[1]);

	n_eq[7]  =   T * U[2];

	n_eq[8]  = -(T * U[2]);

	n_eq[9]  = 0;

	n_eq[10] = 0;

	n_eq[11] = 0;

	n_eq[12] = 0;

	n_eq[13] = 0;

	n_eq[14] = 0;

	break;

    }



}
