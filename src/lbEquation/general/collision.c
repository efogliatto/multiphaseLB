#include <stdlib.h>

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

#include <liMRTModel.h>
#include <liSRTModel.h>
#include <liTempModel.h>


void collision( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {


    // Apply collision model
    switch(field->colId) {

    // Li MRT Model
    case 0:
    	liMRTCollision( mesh, mfields, field );
    	break;


    // Li SRT Model
    case 1:
    	liSRTCollision( mesh, mfields, field );
    	break;

	
    // Li SRT Model. Temperature
    case 2:
    	liTempCollision( mesh, mfields, field );
    	break;
	
	
    default:
    	printf("\n   [ERROR]  Collision model is not yet implemented\n\n");
    	exit(1);
    	break;
	
    }
    

};
