#include <macroDensityInLevel.h>
#include <basic.h>
#include <lbEquation.h>



void macroDensityInLevel( latticeMesh* mesh, macroFields* mfields, lbeField* field, uint level ) {


    if (field->update != 0) {

	
	// Compute density according to field.colId
    
	uint id;
    
    
	// Apply collision model
	switch(field->model) {

	
	// Li MRT Model
	case liMRT:

	    for( id = 0 ; id < mesh->mesh.nPoints ; id++) {

		if( mesh->parallel.level[id] == level )	{
		
		    mfields->rho[id] = liMRTDensity( mesh, field->value[id] );

		}
		
	    }
	
	    break;


	// My MRT Model
	case myMRT:

	    errorMsg("Density update not suitable for myMRTModel");
	
	    break;
	


	// xU MRT Model
	case xuMRT:

	    for( id = 0 ; id < mesh->mesh.nPoints ; id++) {

		if( mesh->parallel.level[id] == level )	{
		    
		    mfields->rho[id] = xuMRTDensity( mesh, field->value[id] );

		}
	    
	    }
	
	    break;


	    
	
	default:

	    errorMsg("Density update not available");

	    break;
	
	}

    }
    
}
