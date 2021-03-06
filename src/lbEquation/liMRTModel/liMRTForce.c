#include <liMRTForce.h>
#include <pseudoPot.h>

/* #include <stdio.h> */
/* #include <totalForce.h> */
/* #include <interactionForce.h> */
/* #include <potential.h> */


void liMRTForce( latticeMesh* mesh, macroFields* mfields, lbeField* field, scalar* S, uint id ) {

    
    if( mesh->lattice.Q == 9 ) {

	
	// Total force
	
	scalar F[3] = { mfields->Ft[id][0], mfields->Ft[id][1], mfields->Ft[id][2] };

	/* uint j; */

	/* for( j = 0 ; j < 3 ; j++ ) { */

	/*     F[j] = mfields->Fi[id][j]  +   (mfields->rho[id] - mesh->EOS.rho_0) * mesh->EOS.g[j]; */

	/* } */


	// Potential
	
	scalar psi = potential( mesh, mfields->rho[id], mfields->T[id]);
	

	S[0] = 0;
	S[1] =  6 * (mfields->U[id][0]*F[0] + mfields->U[id][1]*F[1]) + 12 * field->lbparam.liMRT.sigma * (mfields->Fi[id][0]*mfields->Fi[id][0] + mfields->Fi[id][1]*mfields->Fi[id][1]) / (psi * psi * ((1/field->lbparam.liMRT.Lambda[1])-0.5));
	S[2] = -6 * (mfields->U[id][0]*F[0] + mfields->U[id][1]*F[1]) - 12 * field->lbparam.liMRT.sigma * (mfields->Fi[id][0]*mfields->Fi[id][0] + mfields->Fi[id][1]*mfields->Fi[id][1]) / (psi * psi * ((1/field->lbparam.liMRT.Lambda[2])-0.5));
	S[3] = F[0];
	S[4] = -F[0];
	S[5] = F[1];
	S[6] = -F[1];
	S[7] = 2 * (mfields->U[id][0]*F[0] - mfields->U[id][1]*F[1]);
	S[8] = mfields->U[id][0]*F[1] + mfields->U[id][1]*F[0];	
	
    }

    else {

    	if( mesh->parallel.pid == 0 ) {

    	    printf("\n [ERROR] MRT force squeme not implemented for D%dQ%d \n\n", mesh->lattice.d, mesh->lattice.Q);
	    
    	}

    }

}







/* void liMRTForce( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, scalar* S, unsigned int id ) { */

    
/*     if( mesh->lattice.Q == 9 ) { */

/* 	scalar F[3]; */
/* 	scalar Fm[3]; */
	
/* 	// Total force */
/* 	totalForce( mesh, F, mfields->rho, mfields->T, id); */

/* 	// Interaction force */
/* 	interactionForce( mesh, Fm, mfields->rho, mfields->T, id); */

/* 	// Potential */
/* 	scalar psi = potential( mesh, mfields->rho[id], mfields->T[id]); */
	
/* 	S[0] = 0; */
/* 	S[1] =  6 * (mfields->U[id][0]*F[0] + mfields->U[id][1]*F[1]) + 12 * field->sigma * (Fm[0]*Fm[0] + Fm[1]*Fm[1]) / (psi * psi * ((1/field->Lambda[1])-0.5)); */
/* 	S[2] = -6 * (mfields->U[id][0]*F[0] + mfields->U[id][1]*F[1]) - 12 * field->sigma * (Fm[0]*Fm[0] + Fm[1]*Fm[1]) / (psi * psi * ((1/field->Lambda[2])-0.5)); */
/* 	S[3] = F[0]; */
/* 	S[4] = -F[0]; */
/* 	S[5] = F[1]; */
/* 	S[6] = -F[1]; */
/* 	S[7] = 2 * (mfields->U[id][0]*F[0] - mfields->U[id][1]*F[1]); */
/* 	S[8] = mfields->U[id][0]*F[0] + mfields->U[id][1]*F[1]; */

	
/*     } */

/*     else { */

/*     	if( mesh->parallel.pid == 0 ) { */

/*     	    printf("\n [ERROR] MRT force squeme not implemented for D%dQ%d \n\n", mesh->lattice.d, mesh->lattice.Q); */
	    
/*     	} */

/*     } */

/* } */
