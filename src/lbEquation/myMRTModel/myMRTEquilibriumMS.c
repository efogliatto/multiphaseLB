#include <latticeMesh.h>
#include <macroFields.h>
#include <basic.h>

void myMRTEquilibriumMS( struct latticeMesh* mesh, struct macroFields* mfields, double* n_eq, unsigned int id ) {

    // Up to now, only D2Q9

    if(mesh->lattice.Q == 9) {


	// Velocity U magnitude
	
	double umag = vectorMag2( mfields->U[id] );
	
	
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
	

    }

}
