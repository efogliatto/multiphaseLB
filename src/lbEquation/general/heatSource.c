#include <heatSource.h>
#include <finiteDifference.h>
#include <pseudoPot.h>
#include <basic.h>


void heatSource( latticeMesh* mesh, macroFields* mfields, lbeField* field ) {


    if( field->update != 0 ) {

    
	uint k, id;

	scalar lambda = 1.0,
	    dot = 0.0,
	    divU = 0.0,
	    dpdT = 0.0;

	scalar gradT[3],
	    gradRho[3];

	/* scalar w = 0; */

	/* scalar* n     = (scalar*)malloc( mesh->lattice.Q * sizeof(scalar) );   // m:  momentum space */


    

	switch( field->model ){

	case myMRT:

	    /* w = 6.0 / (4.0 + 3.0 * field->lbparam.myMRT.alpha_1 + 2.0 * field->lbparam.myMRT.alpha_2 ); */

	
	    for( id = 0 ; id < mesh->parallel.nlocal ; id++ ) {

	    
		lambda = mfields->rho[id] * mesh->EOS.Cv * (1/field->lbparam.myMRT.Lambda[3] - 0.5) * (4.0 + 3.0 * field->lbparam.myMRT.alpha_1 + 2.0 * field->lbparam.myMRT.alpha_2) / 6.0;
    

		// Temperature gradient
    
		scalarGradient( gradT, mfields->T, mesh, id );


		///////////////////////////////////////////////////////////////////
		//                        Version de prueba                      //
		///////////////////////////////////////////////////////////////////

	    
		/* // Equilibrium distribution */

		/* matVecMult(mesh->lattice.M, field->value[id], n, mesh->lattice.Q); */


		/* // Temperature gradient */
	    
		/* gradT[0] = -w * ( field->lbparam.myMRT.Lambda[3] * (n[3] - mfields->T[id]*mfields->U[id][0])    +   0.5 * field->lbparam.myMRT.Lambda[3] * field->lbparam.myMRT.Lambda[4] * (n[4] + mfields->T[id]*mfields->U[id][0])); */

		/* gradT[1] = -w * ( field->lbparam.myMRT.Lambda[5] * (n[5] - mfields->T[id]*mfields->U[id][1])    +   0.5 * field->lbparam.myMRT.Lambda[5] * field->lbparam.myMRT.Lambda[6] * (n[4] + mfields->T[id]*mfields->U[id][1])); */

		/* gradT[2] = 0; */
	    

		///////////////////////////////////////////////////////////////////	    

	    


		// 1/rho gradient
    
		invScalarGradient( gradRho, mfields->rho, mesh, id );


		// Velocity divergence

		divU = vectorDivergence( mfields->U, mesh, id );



		dot = 0;
	    
		for( k = 0 ; k < 3 ; k++ ) {

		    dot += gradT[k] * gradRho[k];
	
		}


		dpdT = p_eos(&mesh->EOS, mfields->rho[id], 1.1*mfields->T[id]) - p_eos(&mesh->EOS, mfields->rho[id], 0.9*mfields->T[id]);

		dpdT = dpdT / (0.2*mfields->T[id]);
    
		field->scalarSource[id] = -lambda * dot / mesh->EOS.Cv   +   divU * mfields->T[id]*( 1.0 - dpdT/(mfields->rho[id]*mesh->EOS.Cv) );


	    }
	
	    break;


	    // Li SRT Model
	case liMRT:

	    errorMsg("Heat source not defined for liMRTModel");
	
	    break;
	
	
	
	default:

	    errorMsg("Heat source not defined");

	    break;	

	    

	}


    }


    /* free(n); */

}
