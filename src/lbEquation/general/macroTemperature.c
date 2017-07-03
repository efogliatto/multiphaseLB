#include <stdlib.h>

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

#include <liMRTModel.h>
#include <liSRTModel.h>
#include <liTempModel.h>


void macroTemperature( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {


    unsigned int id;    
    
    // Apply collision model
    switch(field->colId) {

    // Li SRT Model
	
    case 2:

	for( id = 0 ; id < mesh->mesh.nPoints ; id++) {

	    mfields->T[id] = liTempTemperature( mesh, mfields, field, id );

	}
	
	break;
	
    default:
	printf("\n   [ERROR]  Unable to compute macroscopic temperature\n\n");
	exit(1);
	break;	
	
    }

    
}
