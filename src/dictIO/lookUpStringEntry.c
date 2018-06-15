#include <lookUpStringEntry.h>
#include <lookUpEntry.h>
#include <string.h>
#include <stdlib.h>
#include <basic.h>

uint lookUpStringEntry( char* dname, char* ename, char** entry, const char* df ) {


    char* aux = 0;
    
    uint status = 0;

    
    status = lookUpEntry( dname, ename, &aux );
	

    // If ename is not properly found, use df
    
    if(!status) {

	*entry = (char*)malloc( strlen(df) * sizeof(char) );

	strcpy(*entry, df);

    }

    else {

	*entry = (char*)malloc( strlen(aux) * sizeof(char) );

	strcpy(*entry, aux);	

    }

    free(aux);
  
    
    return status;

}
