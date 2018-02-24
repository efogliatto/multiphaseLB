#include <stdlib.h>

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

#include <liMRTModel.h>
#include <liSRTModel.h>
#include <liTempModel.h>
#include <newTempModel.h>
#include <myMRTModel.h>


void macroTemperature( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {


    if (field->update != 0) {

	
	unsigned int id;    
    
	switch(field->colId) {


	    
	// Li SRT Model
	
	case 2:

	    for( id = 0 ; id < mesh->mesh.nPoints ; id++) {

		mfields->T[id] = liTempTemperature( mesh, mfields, field, id );

	    }
	
	    break;



	// myMRTModel
	    
	case 4:

	    for( id = 0 ; id < mesh->mesh.nPoints ; id++) {
		/* for( id = 0 ; id < mesh->parallel.nlocal ; id++) { */

		mfields->T[id] = myMRTTemperature( mesh, mfields, field, id );

	    }
	
	    break;	

	
	default:
	    printf("\n   [ERROR]  Unable to compute macroscopic temperature\n\n");
	    exit(1);
	    break;	
	
	}


    }
    
}
