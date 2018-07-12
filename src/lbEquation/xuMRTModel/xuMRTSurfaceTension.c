#include <xuMRTSurfaceTension.h>
#include <pseudoPot.h>
#include <basic.h>


void xuMRTSurfaceTension( latticeMesh* mesh, macroFields* mfields, lbeField* field, scalar* C, uint id ) {


    // Up to now, only Xu model

    if(field->lbparam.xuMRT.surfaceTension == xuSurfTen) {
    

	/* // Q tensor */

	/* scalar** Q; */

	/* scalar psi = potential( mesh, mfields->rho[id], mfields->T[id]); */

	/* scalar alpha; */

	/* int neighId; */

	/* uint i,j,k, noneigh = 0; */
	

	
	switch( mesh->lattice.model ) {

	case D3Q15:

	    errorMsg("Surface tension model not implemented");
	    

	    /* // Move over neighbours and check for boundary */

	    /* for( k = 1 ; k < mesh->lattice.Q ; k++ ) { */

	    /* 	if( mesh->mesh.nb[id][k] == -1 ) { */
	    
	    /* 	    noneigh++; */
	    
	    /* 	} */

	    /* }	     */


	    /* // Do not use unexisting neighbour */
	    /* if( noneigh == 0 ) { */

		
	    /* 	Q = matrixDoubleAlloc(3, 3, 0); */


	    /* 	// Move over velocities */

	    /* 	for( k = 1 ; k < mesh->lattice.Q ; k++ ) { */

	    /* 	    neighId = mesh->mesh.nb[id][ mesh->lattice.reverse[k] ]; */
		
	    /* 	    alpha = mesh->lattice.weights[k] * ( potential( mesh, mfields->rho[neighId], mfields->T[neighId]) - psi ); */


	    /* 	    for( i = 0 ; i < 2 ; i++ ) { */

	    /* 		for( j = 0 ; j < 2 ; j++ ) { */

	    /* 		    Q[i][j] += alpha * mesh->lattice.vel[k][i] * mesh->lattice.vel[k][j]; */

	    /* 		} */

	    /* 	    } */
		    

	    /* 	} */


	    /* 	for( i = 0 ; i < 2 ; i++ ) { */

	    /* 	    for( j = 0 ; j < 2 ; j++ ) { */

	    /* 		Q[i][j] = Q[i][j] * 0.5 * psi * mesh->EOS.G * field->lbparam.xuMRT.kappa_st; */

	    /* 	    } */

	    /* 	} */



	    /* 	// Complete C array */

	    /* 	C[0] = 0; */

	    /* 	C[1] = 1.5 * field->lbparam.xuMRT.Lambda[1] * (Q[0][0] + Q[1][1]); */

	    /* 	C[2] = -1.5 * field->lbparam.xuMRT.Lambda[2] * (Q[0][0] + Q[1][1]); */

	    /* 	C[3] = 0; */

	    /* 	C[4] = 0; */

	    /* 	C[5] = 0; */

	    /* 	C[6] = 0; */

	    /* 	C[7] = -field->lbparam.xuMRT.Lambda[8] * (Q[0][0] - Q[1][1]); */

	    /* 	C[8] = -field->lbparam.xuMRT.Lambda[8] * Q[0][1]; */



	    /* 	// Deallocate memory */
		
	    /* 	free(Q[0]); */

	    /* 	free(Q[1]); */

	    /* 	free(Q); */


	    /* } */


	    /* // Boundary node */
	    
	    /* else { */

	    /* 	for( k = 0 ; k < 9 ; k++ ) { */

	    /* 	    C[k] = 0; */

	    /* 	} */

	    /* } */

	    break;



	default:

	    errorMsg("Surface tension model not implemented");

	    break;

	}


    }

    
    
    


}
