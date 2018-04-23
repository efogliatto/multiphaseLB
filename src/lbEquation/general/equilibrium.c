#include <equilibrium.h>
#include <basic.h>
#include <liMRTModel.h>
#include <myMRTModel.h>


void equilibrium( latticeMesh* mesh, macroFields* mfields, lbeField* field ) {


    if( field->update != 0 ) {

    
    
	// Apply equilibrium model

	unsigned int id;
    
	switch(field->model) {

	
	    // Li model. MRT version
	
	case liMRT:
	
	    for( id = 0 ; id < mesh->mesh.nPoints ; id++) {

		liMRTEquilibrium( &mesh->lattice, mfields->rho[id], mfields->U[id], field->value[id] );

	    }
	
	    break;

      


	    // new MRT model. Temperature
	
	case myMRT:
	
	    for( id = 0 ; id < mesh->mesh.nPoints ; id++) {

		myMRTEquilibrium( &mesh->lattice, mfields->T[id], mfields->U[id], field->lbparam.myMRT.alpha_1, field->lbparam.myMRT.alpha_2, field->value[id] );
	    
	    }

	
	    break;
	

	    
	default:

	    errorMsg("Unrecognized collision model");       

	    break;

	    
	
	}


    }
    
}
