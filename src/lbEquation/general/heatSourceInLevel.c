#include <heatSourceInLevel.h>
#include <finiteDifference.h>
#include <pseudoPot.h>
#include <basic.h>


void heatSourceInLevel( latticeMesh* mesh, macroFields* mfields, lbeField* field, uint level ) {


    if( field->update != 0 ) {

    
	uint k, id;

	scalar lambda = 1.0,
	    dot = 0.0,
	    divU = 0.0,
	    dpdT = 0.0;

	scalar gradT[3],
	    gradRho[3];


    

	switch( field->model ){

	case myMRT:

	
	    for( id = 0 ; id < mesh->mesh.nPoints ; id++ ) {

		
		if( mesh->parallel.level[id] == level )	{		

		    
		    // Thermal conductivity

		    switch( mesh->lattice.model ) {

		    case D2Q9:
		    
			lambda = mfields->rho[id] * mesh->EOS.Cv * (1/field->lbparam.myMRT.Lambda[3] - 0.5) * (4.0 + 3.0 * field->lbparam.myMRT.alpha_1
													       + 2.0 * field->lbparam.myMRT.alpha_2) / 6.0;

			break;

		    case D3Q15:

			lambda = mfields->rho[id] * mesh->EOS.Cv * (1/field->lbparam.myMRT.Lambda[3] - 0.5) * (6.0 + 11.0 * field->lbparam.myMRT.alpha_1
													       + field->lbparam.myMRT.alpha_2) / 9.0;		    
		    
			break;

		    }
		

		    // Temperature gradient
    
		    scalarGradient( gradT, mfields->T, mesh, id );    


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
