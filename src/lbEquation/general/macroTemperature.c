#include <basic.h>
#include <macroTemperature.h>
#include <myMRTModel.h>


void macroTemperature( latticeMesh* mesh, macroFields* mfields, lbeField* field ) {


    if (field->update != 0) {

	
	uint id;    
    
	switch(field->model) {
	    

	// myMRTModel
	    
	case myMRT:

	    for( id = 0 ; id < mesh->mesh.nPoints ; id++) {

		mfields->T[id] = myMRTTemperature( mesh, mfields, field, id );

	    }
	
	    break;	


	    
      	// Li SRT Model
	case liMRT:

	    errorMsg("Temperature update not suitable for liMRTModel");
	
	    break;
	
	
	
	default:

	    errorMsg("Temperature update not available");

	    break;	

	    
	
	}


    }
    
}
