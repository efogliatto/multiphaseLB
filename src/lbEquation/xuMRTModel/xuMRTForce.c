#include <xuMRTForce.h>
#include <pseudoPot.h>
#include <basic.h>


void xuMRTForce( latticeMesh* mesh, macroFields* mfields, lbeField* field, scalar* S, uint id ) {

    
    if( mesh->lattice.model == D3Q15 ) {

	
	// Total force
	
	scalar F[3];

	uint j;

	for( j = 0 ; j < 3 ; j++ ) {

	    F[j] = mfields->Fi[id][j]  +   (mfields->rho[id] - mesh->EOS.rho_0) * mesh->EOS.g[j];

	}


	// Potential
	
	scalar psi = potential( mesh, mfields->rho[id], mfields->T[id]);


	// Velocity pointer

	scalar U[3] = { mfields->U[id][0], mfields->U[id][1], mfields->U[id][2] };
	

	// u \cdot F
	
	scalar uDotF = U[0]*F[0] + U[1]*F[1] + U[2]*F[2];



	S[0] = 0;

	S[1] = 2.0 * uDotF   +   (6.0 * field->lbparam.xuMRT.sigma * vectorMag2(F)) / (psi*psi*((1/field->lbparam.xuMRT.Lambda[1])-0.5));

	S[2] = -10.0 * uDotF;

	S[3] = F[0];

	S[4] = -7.0 * F[0] / 3.0;

	S[5] = F[1];

	S[6] = -7.0 * F[1] / 3.0;

	S[7] = F[2];

	S[8] = -7.0 * F[2] / 3.0;

	S[9] = 4.0 * U[0]*F[0]  -  2.0 * U[1]*F[1]  -  2.0 * U[2]*F[2];

	S[10] = 2.0 * U[1]*F[1]  -  2.0 * U[2]*F[2];

	S[11] = U[0]*F[1]  +  U[1]*F[0];

	S[12] = U[1]*F[2]  +  U[2]*F[1];

	S[13] = U[0]*F[2]  +  U[2]*F[0];

	S[14] = 0;
	
	
    }



    
    else {

    	if( mesh->parallel.pid == 0 ) {

    	    printf("\n [ERROR] MRT force squeme not implemented for D%dQ%d \n\n", mesh->lattice.d, mesh->lattice.Q);
	    
    	}

    }

}
