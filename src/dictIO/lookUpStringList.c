#include <lookUpStringList.h>
#include <openDict.h>
#include <tokenize.h>
#include <bracedEntry.h>


unsigned int lookUpStringList( char* dname, char* ename, char*** entry, unsigned int* n ) {


    unsigned int status = 0;


    // Open dictionary

    dictionary dict = openDict( dname );

    char* braced = (char*)malloc( strlen(dict.content) * sizeof(char) );

    strcpy(braced, dict.content);

    


    // Tokenize ename

    char** tk;

    unsigned int nn;

    status = tokenize(ename, &tk, &nn);

    

    if(status) {

    	status = 0;


    	// Look for braced entries first

    	unsigned int i;
	

	for( i = 0 ; i < nn ; i++ ) {

	    status = bracedEntry( tk[i], braced, &braced );

		
	    // Stop looking if error is present
		
	    if(!status) {

		i = nn;

	    }

	}


	
	if(status) {
	

	    // Remove special characters       

	    for( i = 0 ; i < strlen(braced) ; i++ ) {

		if( (braced[i] == '\n') ) {

		    braced[i] = ' ';

		}

	    }
	

	    // Count ocurrences in braced as words

	    char* aux = (char*)malloc( strlen(braced)*sizeof(char) );

	    strcpy(aux, braced);

	
	

	    // Count numbers

	    unsigned int count = 0,
		maxl = 0;

	    char* token = strtok(aux, " \n");

	    while(token) {
	    
		count++;

		if( strlen(token) > maxl )
		    maxl = strlen(token);
	    
		token = strtok(NULL, " ");
	    
	    }

	
	    *n = count;





	    // Allocate memory for entry and copy
    
	    *entry = (char**)malloc( count * sizeof(char*) );

	    for( i = 0 ; i < count ; i++ ) {

		(*entry)[i] = (char*)malloc( (maxl+1) * sizeof(char) );

		memset((*entry)[i],'\0',maxl+1);

	    }


	    
	    // Copy elements to *entry

	    i = 0;

	    char* token2 = strtok(braced, " \n");

	    while(token2) {

		strcpy( (*entry)[i], token2);
	    
		token2 = strtok(NULL, " ");

		i++;
	    
	    }	    
	    

	    

	}


    }




    /* // Allocate memory for entry and copy */
    
    /* *entry = (char*)malloc( strlen(braced) * sizeof(char) ); */

    /* strcpy(*entry, braced); */

    /* free(braced); */
    


    return status;

}
