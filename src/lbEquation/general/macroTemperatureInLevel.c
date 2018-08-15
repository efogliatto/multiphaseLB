#include <basic.h>
#include <macroTemperatureInLevel.h>
#include <myMRTModel.h>


void macroTemperatureInLevel( latticeMesh* mesh, macroFields* mfields, lbeField* field, uint level ) {


    if (field->update != 0) {

	
	uint id;    
    
	switch(field->model) {
	    

	// myMRTModel
	    
	case myMRT:

	    for( id = 0 ; id < mesh->mesh.nPoints ; id++) {

		if( mesh->parallel.level[id] == level )	{

		    mfields->T[id] = myMRTTemperature( mesh, mfields, field, id );

		}

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
