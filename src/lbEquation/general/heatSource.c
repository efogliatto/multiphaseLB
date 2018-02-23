#include <heatSource.h>
#include <finiteDifference.h>
#include <pseudoPot.h>
#include <stdlib.h>

void heatSource( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {

    unsigned int i, id;

    double lambda = 1.0,
	dot = 0.0,
	divU = 0.0,
	dpdT = 0.0;

    double gradT[3],
	gradRho[3];


    switch( field->colId ){

    case 4:

	for( id = 0 ; id < mesh->parallel.nlocal ; id++ ) {

	    
	    lambda = mfields->rho[id] * mesh->EOS._Cv * (1/field->Lambda[3] - 0.5) * (4.0 + 3.0 * field->alpha_1 + 2.0 * field->alpha_2) / 6.0;
    

	    // Temperature gradient
    
	    scalarGradient( gradT, mfields->T, mesh, id );


	    // 1/rho gradient
    
	    invScalarGradient( gradRho, mfields->rho, mesh, id );


	    // Velocity divergence

	    divU = vectorDivergence( mfields->U, mesh, id );



	    for( i = 0 ; i < mesh->lattice.Q ; i++ ) {

		dot += gradT[i] * gradRho[i];
	
	    }


	    dpdT = p_eos(&mesh->EOS, mfields->rho[id], 1.1*mfields->T[id]) - p_eos(&mesh->EOS, mfields->rho[id], 0.9*mfields->T[id]);

	    dpdT = dpdT / (0.2*mfields->T[id]);
    
	    field->scalarSource[i] = -lambda * dot / mesh->EOS._Cv   +   divU * mfields->T[id]*( 1.0 - dpdT/(mfields->rho[id]*mesh->EOS._Cv) );


	}
	
	break;


    default:

	printf("\n  [ERROR] Heat source not defined for model %d\n\n", field->colId);

	exit(0);

    }

}
