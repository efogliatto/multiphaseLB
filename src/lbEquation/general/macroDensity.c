#include <macroDensity.h>
#include <basic.h>
#include <lbEquation.h>



void macroDensity( latticeMesh* mesh, macroFields* mfields, lbeField* field, uint start, uint end ) {


    if (field->update != 0) {

	
	// Compute density according to field.colId
    
	uint id;
    
    
	// Apply collision model
	switch(field->model) {

	
	// Li MRT Model
	case liMRT:

	    for( id = start ; id < end ; id++) {
	    
		mfields->rho[id] = liMRTDensity( mesh, field->value[id] );
	    
	    }
	
	    break;


	// My MRT Model
	case myMRT:

	    errorMsg("Density update not suitable for myMRTModel");
	
	    break;


	// Li Temp MRT Model
	case liTempMRT:

	    errorMsg("Density update not suitable for liTempMRTModel");
	
	    break;
	    


	// xU MRT Model
	case xuMRT:

	    for( id = start ; id < end ; id++) {
	    
		mfields->rho[id] = xuMRTDensity( mesh, field->value[id] );
	    
	    }
	
	    break;


	    
	
	default:

	    errorMsg("Density update not available");

	    break;
	
	}

    }
    
}
