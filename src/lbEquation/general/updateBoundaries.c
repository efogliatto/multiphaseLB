#include <lbeField.h>
#include <macroFields.h>
#include <latticeMesh.h>
#include <bounceBack.h>
#include <fixedT.h>
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
	    
        // fixedT
    	case 3:
    	    fixedT( mesh, mfields, field, bndId );
    	    break;
    
    	default:
    	    printf("\n  [ERROR]  Unrecognized boundary condition \n\n\n");
    	    exit(1);
	    

    	}

	
    }







    // Move over boundaries and update boundary elements
    
    for( bndId = 0 ; bndId < mesh->mesh.bd.nbd ; bndId++ ) {

	
    	/* if( field->boundary[bndId].bdType != 0 ) { */
	

    	    unsigned i,j;
	

    	    // Apply collision model
    	    switch(field->colId) {

    		// Li MRT Model
    	    case 0:
	    
    		for( i = 0 ; i < mesh->mesh.bd.nbdelem[bndId] ; i++ ) {

    		    j = mesh->mesh.bd.bdPoints[bndId][i];

    		    mfields->rho[j] = liMRTDensity( mesh, field->value[j] );

    		    liMRTVelocity( mesh, mfields, field, mfields->U, j );

    		}
	    
    		break;


    		// Li SRT Model
    	    case 1:

    		for( i = 0 ; i < mesh->mesh.bd.nbdelem[bndId] ; i++ ) {

    		    j = mesh->mesh.bd.bdPoints[bndId][i];

    		    mfields->rho[j] = liSRTDensity( mesh, field->value[j] );

    		    liSRTVelocity( mesh, mfields, field, mfields->U, j );

    		}
	    
    		break;

	
    		// Li SRT Model. Temperature
    	    case 2:

    		for( i = 0 ; i < mesh->mesh.bd.nbdelem[bndId] ; i++ ) {

    		    j = mesh->mesh.bd.bdPoints[bndId][i];

    		    mfields->T[j] = liTempTemperature( mesh, mfields, field, j );

    		}
	    
    		break;
	
	
    	    default:
    		printf("\n   [ERROR]  Collision model is not yet implemented\n\n");
    		exit(1);
    		break;
	
    	    }

	
    	/* } */
	
    }
    

    
}
