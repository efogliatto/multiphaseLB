#include <stdlib.h>

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

#include <liMRTModel.h>
#include <liSRTModel.h>
#include <liTempModel.h>


void macroDensity( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {

    
    // Compute density according to field.colId
    
    unsigned int id;
    
    
    // Apply collision model
    switch(field->colId) {

	
    // Li MRT Model
    case 0:

	for( id = 0 ; id < mesh->mesh.nPoints ; id++) {
	    
	    mfields->rho[id] = liMRTDensity( mesh, field->value[id] );
	    
	}
	
	break;


    // Li SRT Model
    case 1:

	for( id = 0 ; id < mesh->mesh.nPoints ; id++) {
	    
	    mfields->rho[id] = liSRTDensity( mesh, field->value[id] );
	    
	}
	
	break;
	
	
	
    default:
	printf("\n\n[ERROR]  Model not available \n\n");
	exit(1);
	break;	
	
    }

}
