#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <latticeVelocities.h>

int** latticeVelocities( char* modelName ) {

    int** vel;

    if ( strcmp(modelName,"D2Q9") == 0 ) {

	vel = D2Q9_Vel();
	
    }

    return vel;

}

/*     // Pseudopotential weights */

/*     _weights.push_back( 0 ); */
/*     _weights.push_back(1.0/3); */
/*     _weights.push_back(1.0/3); */
/*     _weights.push_back(1.0/3); */
/*     _weights.push_back(1.0/3); */
/*     _weights.push_back(1.0/12); */
/*     _weights.push_back(1.0/12); */
/*     _weights.push_back(1.0/12); */
/*     _weights.push_back(1.0/12); */
    
/* } */


/* // Default destructor */
/* D2Q9::~D2Q9() {} */



/* // Acces members */
/* const uint& D2Q9::D() const { */
/*     return _D; */
/* } */



/* // Main index */
/* const bool D2Q9::is_principal(const uint& id) const { */
/*     return ( (id <= 4)  &&  (id > 0) ) ? true : false;     */
/* } */
