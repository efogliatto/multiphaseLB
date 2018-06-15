#include <myMRTTemperature.h>
#include <myMRTSource.h>
#include <stdlib.h>

scalar myMRTTemperature( latticeMesh* mesh, macroFields* mfields, lbeField* field, uint id ) {

    uint k;


    // Initialize Temperature
    scalar T = 0;

    
    // Implicit source term
    
    scalar* Gamma = (scalar*)malloc( mesh->lattice.Q * sizeof(scalar) );

    myMRTSource(mesh, mfields, field, Gamma, id);


    
    // Move over model velocities

    for(k = 0 ; k < mesh->lattice.Q ; k++) {

	T += field->value[id][k];
		    
    }

    T = T + 0.5 * Gamma[0];


    
    free(Gamma);


    return T;
	
}
