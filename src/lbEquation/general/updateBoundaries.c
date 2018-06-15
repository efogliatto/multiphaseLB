#include <updateBoundaries.h>
#include <boundary.h>
#include <basic.h>


void updateBoundaries( latticeMesh* mesh, macroFields* mfields, lbeField* field ) {


    if( field->update != 0 ) {
    
	uint bndId;

    
	// Move over boundaries and apply condition
    
	for( bndId = 0 ; bndId < mesh->mesh.bd.nbd ; bndId++ ) {


	    switch( field->boundary[bndId].type ) {


		// none - periodic
	    case periodic:
		break;
	    
		// bounceBack
	    case bback:
		bounceBack( mesh, mfields, field->value, bndId );
		break;

		// fixedU
	    case fu:
		fixedU( mesh, mfields, field->value, bndId, field->model, &(field->boundary[bndId].param), &(field->lbparam) );
		break;	    
	    
		// fixedT
	    case ft:
		fixedT( mesh, mfields, field->value, bndId, field->model, &(field->boundary[bndId].param), &(field->lbparam) );
		break;

		// Outflow
	    case of:
		outflow( mesh, mfields, field->value, bndId );
		break;

		// Fixed EOS pressure
	    case fep:
		/* fixedEOSp( mesh, mfields, field, bndId ); */
		break;

		// Fixed heat flux
	    case uhf:
		/* uniformHeatFlux( mesh, mfields, field, bndId ); */
		break;
	    
	    default:
		
		errorMsg("Unrecognized boundary condition");
		
		break;

	    }

	
	}
    
    }
    
}
