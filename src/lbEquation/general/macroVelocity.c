#include <macroVelocity.h>
#include <basic.h>
#include <liMRTModel.h>


void macroVelocity( latticeMesh* mesh, macroFields* mfields, lbeField* field ) {


    if (field->update != 0) {
    
	// Compute density according to field.colId
    
	uint id;
    
    
	// Apply collision model
	switch(field->model) {

	
	    // Li MRT Model
	case liMRT:

	    for( id = 0 ; id < mesh->mesh.nPoints ; id++) {
	    
		liMRTVelocity( mesh, mfields, field, mfields->U, id );
	    
	    }
	
	    break;


	    // my MRT Model
	case myMRT:

	    errorMsg("Velocity update not suitable for myMRTModel");
	
	    break;
	

	
	default:

	    errorMsg("Velocity update not available");
	    
	    break;	
	
	}


    }
    
}
