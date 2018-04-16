#include <lookUpScalarEntry.h>
#include <lookUpEntry.h>
#include <string.h>
#include <stdlib.h>

unsigned int lookUpScalarEntry( char* dname, char* ename, const double df, double* entry ) {

    
    char* aux = 0;
    
    unsigned int status = lookUpEntry( dname, ename, &aux );


    // If ename is not properly found, use df
    
    if(!status) {

	*entry = df;

    }

    else {

	char* end;
	
	*entry = strtod( aux, &end );

    }


    free(aux);


    return status;

}
