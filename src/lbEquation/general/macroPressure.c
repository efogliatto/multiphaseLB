#include <macroPressure.h>
#include <basic.h>
#include <liMRTModel.h>
#include <xuMRTModel.h>



void macroPressure( latticeMesh* mesh, macroFields* mfields, lbeField* field ) {


    if (field->update != 0) {

	
	// Compute pressure according to field.model
    
	uint id;
    
    
	// Apply collision model
	switch(field->model) {

	
	    // Li MRT Model
	case liMRT:

	    for( id = 0 ; id < mesh->parallel.nlocal ; id++) {
	    
		mfields->p[id] = liMRTPressure( mesh, mfields->rho, mfields->T, field->lbparam.liMRT.sigma, id );
	    
	    }
	
	    break;


	    // Li SRT Model
	case myMRT:

	    errorMsg("Pressure update not suitable for myMRTModel");
	
	    break;
	


	// Xu MRT Model
	case xuMRT:

	    for( id = 0 ; id < mesh->parallel.nlocal ; id++) {
	    
		mfields->p[id] = xuMRTPressure( mesh, field, mfields->rho, mfields->T, field->lbparam.liMRT.sigma, id );
	    
	    }
	
	    break;



	    
	
	default:

	    errorMsg("Pressure update not available");

	    break;	
	
	}

    }
    
}
