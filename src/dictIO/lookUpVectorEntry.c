#include <lookUpVectorEntry.h>
#include <lookUpEntry.h>
#include <string.h>
#include <stdlib.h>

uint lookUpVectorEntry( char* dname, char* ename, scalar** entry, uint* n ) {

    
    char* aux = 0;
    
    uint status = lookUpEntry( dname, ename, &aux );



    // If ename is not properly found, use df
    
    if(!status) {

    	*n = 0;

    }

    else {


	// Remove delimiters

	uint i;

	for( i = 0 ; i < strlen(aux) ; i++ ) {

	    if( (aux[i] == '(') || (aux[i] == ')') ) {

		aux[i] = ' ';

	    }

	}



	char* aux2 = (char*)malloc( strlen(aux)*sizeof(char) );

	strcpy(aux2, aux);

	
	

	// Count numbers

	uint count = 0;

	char* token = strtok(aux, "( )");

	while(token) {
	    
	    count++;
	    
	    token = strtok(NULL, " ");
	    
	}

	
	*n = count;



	// Allocate memory

	*entry = (scalar*)malloc( count * sizeof(scalar) );

	for(i = 0 ; i < count ; i++)
	    (*entry)[i] = 0;




	// Copy numbers to *entry

	i = 0;

	char* token2 = strtok(aux2, "( )");

	while(token2) {

	    char* end;

	    (*entry)[i] = strtod(token2, &end);
	    
	    token2 = strtok(NULL, " ");

	    i++;
	    
	}




	free(token);

	free(token2);

	free(aux2);
	

    }


    free(aux);


    return status;

}
