#include <lookUpIntegerEntry.h>
#include <lookUpEntry.h>
#include <string.h>
#include <stdlib.h>
#include <basic.h>
#include <stdarg.h>


uint lookUpIntegerEntry( char* dname, char* ename, const int df, int* entry ) {

       
    char* aux = 0;

    
    uint status = lookUpEntry( dname, ename, &aux );
    

    // If ename is not properly found, use df
    
    if(!status) {

    	*entry = df;

    }

    else {

    	*entry = atoi( aux );

    }


    free(aux);


    return status;

}
