#include <basic.h>
#include <macroTemperature.h>
#include <myMRTModel.h>
#include <liTempMRTModel.h>


void macroTemperature( latticeMesh* mesh, macroFields* mfields, lbeField* field, uint start, uint end ) {


    if (field->update != 0) {

	
	uint id;    
    
	switch(field->model) {
	    

	// myMRTModel
	    
	case myMRT:

	    for( id = start ; id < end ; id++) {

		mfields->T[id] = myMRTTemperature( mesh, mfields, field, id );

	    }
	
	    break;	



	// myMRTModel
	    
	case liTempMRT:

	    for( id = start ; id < end ; id++) {

		mfields->T[id] = liTempMRTTemperature( mesh, mfields, field, id );

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
