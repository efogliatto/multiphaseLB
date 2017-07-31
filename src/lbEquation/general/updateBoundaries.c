#include <lbeField.h>
#include <macroFields.h>
#include <latticeMesh.h>
#include <bounceBack.h>
#include <fixedT.h>
#include <fixedEOSp.h>
#include <fixedU.h>
#include <outflow.h>

#include <stdlib.h>

#include <liMRTModel.h>
#include <liSRTModel.h>
#include <liTempModel.h>


void updateBoundaries( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field ) {

    
    unsigned int bndId;

    
    // Move over boundaries and apply condition
    
    for( bndId = 0 ; bndId < mesh->mesh.bd.nbd ; bndId++ ) {


    	switch( field->boundary[bndId].bdType ) {


	// none - periodic
    	case 0:
    	    break;
	    
        // bounceBack
    	case 1:
	    bounceBack( mesh, mfields, field, bndId );
    	    break;

        // fixedU
    	case 2:
    	    fixedU( mesh, mfields, field, bndId );
    	    break;	    
	    
        // fixedT
    	case 3:
    	    fixedT( mesh, mfields, field, bndId );
    	    break;

        // Outflow
	case 4:
	    outflow( mesh, mfields, field, bndId );
	    break;

	// Fixed EOS pressure
	case 5:
	    fixedEOSp( mesh, mfields, field, bndId );
	    break;
	    
    	default:
    	    printf("\n  [ERROR]  Unrecognized boundary condition \n\n\n");
    	    exit(1);
	    

    	}

	
    }
    

    
}
