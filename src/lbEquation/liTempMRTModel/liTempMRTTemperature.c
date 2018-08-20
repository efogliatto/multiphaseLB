#include <liTempMRTTemperature.h>
#include <liTempMRTSource.h>
#include <stdlib.h>

scalar liTempMRTTemperature( latticeMesh* mesh, macroFields* mfields, lbeField* field, uint id ) {

    uint k;


    // Initialize Temperature
    scalar T = 0;   

    
    // Move over model velocities

    for(k = 0 ; k < mesh->lattice.Q ; k++) {

	T += field->value[id][k];
		    
    }



    return T;
	
}
