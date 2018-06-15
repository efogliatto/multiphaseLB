#include <myMRTEquilibriumMS.h>
#include <basic.h>

void myMRTEquilibriumMS( latticeMesh* mesh, macroFields* mfields, scalar* n_eq, scalar alpha_1, scalar alpha_2, uint id ) {

    // Up to now, only D2Q9

    if(mesh->lattice.model == D2Q9) {

	
    	// Compute equilibrium in momentum space
	
    	n_eq[0] = mfields->T[id];
	
    	n_eq[1] = alpha_1 * mfields->T[id];
	
    	n_eq[2] = alpha_2 * mfields->T[id];
	
    	n_eq[3] = mfields->T[id] * mfields->U[id][0];
	
    	n_eq[4] = mfields->T[id] * (-mfields->U[id][0]);
	
    	n_eq[5] = mfields->T[id] * mfields->U[id][1];
	
    	n_eq[6] = mfields->T[id] * (-mfields->U[id][1]);
	
    	n_eq[7] = 0;
	
    	n_eq[8] = 0;
	

    }

}
