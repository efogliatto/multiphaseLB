#include <latticeMesh.h>
#include <macroFields.h>
#include <basic.h>

void myMRTEquilibriumMS( struct latticeMesh* mesh, struct macroFields* mfields, double* n_eq, double alpha_1, double alpha_2, unsigned int id ) {

    // Up to now, only D2Q9

    if(mesh->lattice.Q == 9) {

	
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
