#include <stdlib.h>

#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>

#include <liSRTModel.h>
#include <liTempModel.h>
#include <myMRTModel.h>


double singleNodeT( latticeMesh* mesh, macroFields* mfields, lbeField* field, unsigned int id ) {


    double T;
    
    
    // Apply collision model
    
    switch(field->colId) {

	
    // Li SRT Model
	
    case 2:

	T = liTempTemperature( mesh, mfields, field, id );
	
	break;

	

    // myMRTModel
	
    case 4:
	
	T = myMRTTemperature( mesh, mfields, field, id );
       
	break;	

	
    default:
	
	printf("\n   [ERROR]  Unable to compute macroscopic temperature\n\n");
	
	exit(1);
	
	break;	
	
    }


    return T;

    
}
