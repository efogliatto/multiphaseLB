#include <isBracedEntryDefined.h>
#include <openDict.h>
#include <tokenize.h>
#include <bracedEntry.h>
#include <string.h>
#include <stdlib.h>

unsigned int isBracedEntryDefined( char* dname, char* ename ) {


    unsigned int status = 0;


    // Open dictionary

    struct dictionary dict = openDict( dname );

    char* braced = (char*)malloc( strlen(dict.content) * sizeof(char) );

    strcpy(braced, dict.content);

    


    // Tokenize ename

    char** tk;

    unsigned int n;

    status = tokenize(ename, &tk, &n);


    if(status) {

    	status = 0;


    	// Look for braced entries

    	unsigned int i;
	
    	if( n > 1 ){

    	    for( i = 0 ; i < n ; i++ ) {		
		
    		status = bracedEntry( tk[i], braced, &braced );

		
		// Stop looking if error is present
		
		if(!status) {

		    i = n;

		}

    	    }

    	}
	

    }


    return status;


}
