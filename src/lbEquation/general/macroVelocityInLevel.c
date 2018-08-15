#include <macroVelocityInLevel.h>
#include <basic.h>
#include <lbEquation.h>


void macroVelocityInLevel( latticeMesh* mesh, macroFields* mfields, lbeField* field, uint level ) {


    if (field->update != 0) {
    
	// Compute density according to field.colId
    
	uint id;
    
    
	// Apply collision model
	switch(field->model) {

	
	// Li MRT Model
	case liMRT:

	    for( id = 0 ; id < mesh->mesh.nPoints ; id++) {

		if( mesh->parallel.level[id] == level )	{
	    
		    liMRTVelocity( mesh, mfields, field, mfields->U, id );

		}
	    
	    }
	
	    break;


	    // my MRT Model
	case myMRT:

	    errorMsg("Velocity update not suitable for myMRTModel");
	
	    break;



        // Xu MRT Model
	case xuMRT:

	    for( id = 0 ; id < mesh->mesh.nPoints ; id++) {

		if( mesh->parallel.level[id] == level )	{
		
		    xuMRTVelocity( mesh, mfields, field, mfields->U, id );

		}
	    
	    }
	
	    break;
	    

	
	default:

	    errorMsg("Velocity update not available");
	    
	    break;	
	
	}


    }
    
}
