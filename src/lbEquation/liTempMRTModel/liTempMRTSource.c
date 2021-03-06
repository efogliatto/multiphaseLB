#include <liTempMRTSource.h>


void liTempMRTSource( latticeMesh* mesh, macroFields* mfields, lbeField* field, scalar* Gamma, uint id ) {

    uint i;

    /* scalar lambda = 1.0, */
    /* 	dot = 0.0, */
    /* 	divU = 0.0, */
    /* 	dpdT = 0.0; */

    /* scalar gradT[3], */
    /* 	gradRho[3]; */
    

    for( i = 0 ; i < mesh->lattice.Q ; i++ ) {

	Gamma[i] = 0;

    }


    Gamma[0] = field->scalarSource[id];

    /* lambda = mfields->rho[id] * mesh->EOS._Cv * (1/field->Lambda[3] - 0.5) * (4.0 + 3.0 * field->alpha_1 + 2.0 * field->alpha_2) / 6.0; */
    

    /* // Temperature gradient */
    
    /* scalarGradient( gradT, mfields->T, mesh, id ); */


    /* // 1/rho gradient */
    
    /* invScalarGradient( gradRho, mfields->rho, mesh, id ); */


    /* // Velocity divergence */

    /* divU = vectorDivergence( mfields->U, mesh, id ); */



    /* for( i = 0 ; i < mesh->lattice.Q ; i++ ) { */

    /* 	dot += gradT[i] * gradRho[i]; */
	
    /* } */



    
    /* dpdT = p_eos(&mesh->EOS, mfields->rho[id], 1.1*mfields->T[id]) - p_eos(&mesh->EOS, mfields->rho[id], 0.9*mfields->T[id]); */

    /* dpdT = dpdT / (0.2*mfields->T[id]); */
    
    /* Gamma[0] = -lambda * dot / mesh->EOS._Cv   +   divU * mfields->T[id]*( 1.0 - dpdT/(mfields->rho[id]*mesh->EOS._Cv) ); */

}
