#include <stdlib.h>
#include <vectorMag2.h>

scalar vectorMag2( scalar v[3] ) {

    unsigned int k;

    scalar mag = 0;

    for( k = 0 ; k < 3 ; k++ ) {

	mag += v[k] * v[k];

    }


    return mag;

}
