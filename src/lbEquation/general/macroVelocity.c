#include <stdlib.h>

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

#include <liMRTModel.h>
#include <liSRTModel.h>
#include <liTempModel.h>


void macroVelocity( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {

    
    // Compute density according to field.colId
    
    unsigned int id;
    
    
    // Apply collision model
    switch(field->colId) {

	
    // Li MRT Model
    case 0:

	for( id = 0 ; id < mesh->mesh.nPoints ; id++) {
	    
	    liMRTVelocity( mesh, mfields, field, mfields->U, id );
	    
	}
	
	break;


    // Li SRT Model
    case 1:

	for( id = 0 ; id < mesh->mesh.nPoints ; id++) {
	    
	    liSRTVelocity( mesh, mfields, field, mfields->U, id );
	    
	}
	
	break;
	

	
    default:
	printf("\n   [ERROR]  Unable to compute macroscopic velocity\n\n");
	exit(1);
	break;	
	
    }

    
}
