#include <singleEntry.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

uint singleEntry( char* ename, char* content, char** entry ) {

    
    uint status = 0;
    /* printf("\n\n%s\n\n",ename); */

    // Find ename occurrence

    char *partial = strstr(content, ename);


    if( partial != NULL ) {


	
	// Move past ename and whitespaces
	
	partial = partial + strlen(ename) + 1;


	
	// Find first ; occurrence

	char *partial2 = strchr(partial, ';');

	size_t l = strlen(partial) - strlen(partial2);




	// Create a first copy. This enables the use of the same pointer for content and *entry

	char *aux = (char*)malloc( (l+1)*sizeof(char) );

	memset(aux,'\0',l+1);

	strncpy( aux, partial, l );
	

	
	
	// (Re)Allocate memory for entry and copy

	if(entry != NULL) {

	    free(*entry);	   

	}

	
	*entry = (char*)malloc( (l)*sizeof(char) );

	memset(*entry,'\0',l);

	strcpy( *entry, aux );
	
	free(aux);
	
	status = 1;	



    }

    

    return status;

}
