#include <lookUpScalarEntry.h>
#include <lookUpEntry.h>
#include <string.h>
#include <stdlib.h>
#include <basic.h>

uint lookUpScalarEntry( char* dname, char* ename, const scalar df, scalar* entry ) {

    
    char* aux = 0;

    
    uint status = lookUpEntry( dname, ename, &aux );
    

    // If ename is not properly found, use df
    
    if(!status) {

	*entry = df;

    }

    else {

	char* end;

	#ifdef DP
	
	*entry = strtod( aux, &end );

	#elif SP

	*entry = strtof( aux, &end );

	#endif

    }


    free(aux);


    return status;

}
