/*

  Return double from file

  Tokenizes entry and returns elements as double

 */


#include <lookUpEntry.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>




unsigned int lookUpVector( char* fileName, char* entry, double v[], unsigned int vsize ) {


    unsigned int retval = 0,
	ns,
	status;

    char aux[10][100];
    
    status = lookUpEntry( fileName, entry, aux, &ns );

    if (status) {

	if ( ns == vsize ) {

	    uint i;

	    for( i = 0 ; i < ns ; i++ ) {

		v[i] = atof( aux[i] );

	    }

	    retval = 1;

	}

	else {

	    printf("\n   [ERROR]   Ill defined entry %s. Dimension mismatch\n\n", entry);

	    exit(1);

	}

    }
    

    
    return retval;
    

}
