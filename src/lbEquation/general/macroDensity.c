#include <macroDensity.h>
#include <basic.h>
#include <liMRTModel.h>



void macroDensity( latticeMesh* mesh, macroFields* mfields, lbeField* field ) {


    if (field->update != 0) {

	
	// Compute density according to field.colId
    
	unsigned int id;
    
    
	// Apply collision model
	switch(field->model) {

	
	    // Li MRT Model
	case liMRT:

	    for( id = 0 ; id < mesh->mesh.nPoints ; id++) {
	    
		mfields->rho[id] = liMRTDensity( mesh, field->value[id] );
	    
	    }
	
	    break;


	    // Li SRT Model
	case myMRT:

	    errorMsg("Density update not suitable for myMRTModel");
	
	    break;
	
	
	
	default:

	    errorMsg("Density update not available");

	    break;	
	
	}

    }
    
}
