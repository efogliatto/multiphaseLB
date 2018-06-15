#include <lookUpEntry.h>
#include <openDict.h>
#include <tokenize.h>
#include <bracedEntry.h>
#include <singleEntry.h>
#include <basic.h>


uint lookUpEntry( char* dname, char* ename, char** entry ) {


    uint status = 0;


    // Open dictionary

    dictionary dict = openDict( dname );

    char* braced = (char*)malloc( strlen(dict.content) * sizeof(char) );

    strcpy(braced, dict.content);




    // Tokenize ename

    char** tk;

    uint n;

    status = tokenize(ename, &tk, &n);


    if(status) {

    	status = 0;


    	// Look for braced entries first

    	uint i;
	
    	if( n > 1 ){

    	    for( i = 0 ; i < (n-1) ; i++ ) {
		
    		status = bracedEntry( tk[i], braced, &braced );
		
		
		// Stop looking if error is present
		
		if(!status) {

		    i = n;

		}

    	    }



	    // Single entry at last

	    if(status) {

	      status = singleEntry( tk[n-1], braced, &braced );

	    }

    	}



	// No braced entry, only single
	
	else {

	    status = singleEntry( ename, braced, &braced );
	    
	}



	// Memory release

	if(n>1) {

	     for( i = 0 ; i < (n-1) ; i++ ) {

		 free(tk[i]);
		 
	     }
	    
	}
	
	free(tk);
	

    }



    // Allocate memory for entry and copy
    
    *entry = (char*)malloc( strlen(braced) * sizeof(char) );

    strcpy(*entry, braced);

    free(braced);
    


    return status;

}
