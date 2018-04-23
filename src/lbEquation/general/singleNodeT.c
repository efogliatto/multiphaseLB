#include <singleNodeT.h>
#include <basic.h>
#include <myMRTModel.h>


double singleNodeT( latticeMesh* mesh, macroFields* mfields, lbeField* field, unsigned int id ) {


    double T = 0;
    
    
    // Apply collision model
    
    switch(field->model) {
	

    // myMRTModel
	
    case myMRT:
	
	T = myMRTTemperature( mesh, mfields, field, id );
       
	break;	


    // Li SRT Model
    case liMRT:

	errorMsg("Temperature not suitable for liMRTModel");
	
	break;
	
	
	
    default:

	errorMsg("Temperature not available");

	break;	


	
    }


    return T;

    
}
