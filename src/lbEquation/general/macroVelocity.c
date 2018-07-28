#include <macroVelocity.h>
#include <basic.h>
#include <lbEquation.h>


void macroVelocity( latticeMesh* mesh, macroFields* mfields, lbeField* field, uint start, uint end ) {


    if (field->update != 0) {
    
	// Compute density according to field.colId
    
	uint id;
    
    
	// Apply collision model
	switch(field->model) {

	
	// Li MRT Model
	case liMRT:

	    for( id = start ; id < end ; id++) {
	    
		liMRTVelocity( mesh, mfields, field, mfields->U, id );
	    
	    }
	
	    break;


	    // my MRT Model
	case myMRT:

	    errorMsg("Velocity update not suitable for myMRTModel");
	
	    break;



        // Xu MRT Model
	case xuMRT:

	    for( id = start ; id < end ; id++) {
	    
		xuMRTVelocity( mesh, mfields, field, mfields->U, id );
	    
	    }
	
	    break;
	    

	
	default:

	    errorMsg("Velocity update not available");
	    
	    break;	
	
	}


    }
    
}
