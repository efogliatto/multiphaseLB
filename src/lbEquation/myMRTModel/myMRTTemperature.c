#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>
#include <myMRTSource.h>
#include <stdlib.h>

double myMRTTemperature( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int id ) {

    unsigned int k;


    // Initialize Temperature
    double T = 0;

    
    // Implicit source term
    
    double* Gamma = (double*)malloc( mesh->lattice.Q * sizeof(double) );

    myMRTSource(mesh, mfields, field, Gamma, id);


    
    // Move over model velocities

    for(k = 0 ; k < mesh->lattice.Q ; k++) {

	T += field->value[id][k];
		    
    }

    T = T + 0.5 * Gamma[0];


    
    free(Gamma);


    return T;
	
}
