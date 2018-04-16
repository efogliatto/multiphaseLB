#include <singleEntry.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int singleEntry( char* ename, char* content, char** entry ) {

    
    unsigned int status = 0;


    // Find ename occurrence

    char *partial = strstr(content, ename);


    if( partial != NULL ) {


	
	// Move past ename and whitespaces
	
	partial = partial + strlen(ename);

	partial = partial + strspn(partial, " ");


	
	// Find first ; occurrence

	char *partial2 = strchr(partial, ';');

	size_t l = strlen(partial) - strlen(partial2);



	// Create a first copy. This enables the use of the same pointer for content and *entry

	char *aux = (char*)malloc( (l)*sizeof(char) );

	memset(aux,'\0',l);

	strncpy( aux, partial, l );
	
	
	
	// (Re)Allocate memory for entry and copy

	if(entry != NULL) {

	    free(*entry);	   

	}

	
	*entry = (char*)malloc( (l)*sizeof(char) );

	memset(*entry,'\0',l);

	strcpy( *entry, aux );
	
	status = 1;	



    }

    

    return status;

}
