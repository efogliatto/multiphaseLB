#include <collision.h>
#include <basic.h>
#include <liMRTModel.h>
#include <myMRTModel.h>


void collision( latticeMesh* mesh, macroFields* mfields, lbeField* field ) {


    if( field->update != 0 ) {
    

	// Apply collision model
	switch(field->model) {
	    

	    // Li MRT Model
	    
	case liMRT:
	    
	    liMRTCollision( mesh, mfields, field );
	    
	    break;


	    
	    // new Temperature MRT model
	    
	case myMRT:
	    
	    myMRTCollision( mesh, mfields, field );
	    
	    break;		

	
	default:
	    
	    errorMsg("Collision model is not yet implemented");

	    break;
	
	}
    

    }
    
};
