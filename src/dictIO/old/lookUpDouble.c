/*

  Return double from file

  Tokenizes entry and returns elements as double

 */


#include <tokenize.h>
#include <entryList.h>
#include <subEntryList.h>
#include <singleEntryList.h>
#include <lookUpEntry.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned int uint;



unsigned int lookUpDouble( char* fileName, char* entry, double* val, double df ) {

    
    unsigned int retval = 0,
	ns,
	status;

    char aux[10][100];
    
    status = lookUpEntry( fileName, entry, aux, &ns );

    if (status) {

	*val = atof( aux[0] );

	retval = 1;

    }

    else {

	*val = df;

    }
    
    
    return retval;
    
    

}
