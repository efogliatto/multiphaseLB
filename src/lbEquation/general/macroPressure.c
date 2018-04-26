#include <macroPressure.h>
#include <basic.h>
#include <liMRTModel.h>



void macroPressure( latticeMesh* mesh, macroFields* mfields, lbeField* field ) {


    if (field->update != 0) {

	
	// Compute pressure according to field.model
    
	unsigned int id;
    
    
	// Apply collision model
	switch(field->model) {

	
	    // Li MRT Model
	case liMRT:

	    for( id = 0 ; id < mesh->mesh.nPoints ; id++) {
	    
		mfields->p[id] = liMRTPressure( mesh, mfields->rho, mfields->T, id );
	    
	    }
	
	    break;


	    // Li SRT Model
	case myMRT:

	    errorMsg("Pressure update not suitable for myMRTModel");
	
	    break;
	
	
	
	default:

	    errorMsg("Pressure update not available");

	    break;	
	
	}

    }
    
}
