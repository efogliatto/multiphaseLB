#include <latticeMesh.h>
#include <macroFields.h>
#include <lbeField.h>


double newTempTemperature( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int id ) {

    unsigned int k;


    // Initialize Temperature
    double T = 0;


    // Move over model velocities
    for(k = 0 ; k < mesh->lattice.Q ; k++) {

	T += field->value[id][k];
		    
    }


    // Compute T
    T = (T - 0.5 * mfields->phiDivU[id]) / (mfields->rho[id] * mesh->EOS._Cv);


    return T;
    
}
