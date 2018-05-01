#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <basic.h>

unsigned int bracedEntry( char* ename, char* content, char** entry ) {

   
    
    unsigned int status = 0;

    char *partial = strstr(content, ename);

    

    // Not wanted, but there can multiple entries (maybe nested)

    unsigned int isEntry = 0;

    while(  ( isEntry == 0 )  &&  (partial != NULL)  ) {


	// Check ename + { ocurrence
	partial = strstr(partial, ename);
	    
	
	if( partial != NULL ) {
	

	    // Find first character

	    partial = partial + strlen(ename);
	
	    char c = partial[0];
	
	    while(  (c == ' ')  ||  (c == '\n') )   {

		partial++;
	    
		c = partial[0];
	    
	    }

	

	    // Continue only if character is opening brace
      
	    if( c == '{' ) {


		isEntry = 1;
	
	    

		// Find corresponding }

		unsigned int bcount = 1,
		    j = 1;

		while(   ( j < strlen(partial) )   &&   ( bcount != 0 )   )  {

		    c = partial[j];
		
		    if ( c == '{' ) {

			bcount++;

		    }

		    else {
		    
			if ( c == '}' ) {

			    bcount--;

			}

		    }

		    j++;

		}




	    
		// Copy if found

		if( bcount == 0 ) {



		    // Create a first copy. This enables the use of the same pointer for content and *entry

		    char *aux = (char*)malloc( (j-2)*sizeof(char) );

		    memset(aux,'\0', (j-2));

		    strncpy( aux, &partial[1], (j-2) );



		    // (Re)Allocate memory for entry and copy
		
		    if(entry != NULL) {

			free(*entry);

		    }
		
		    *entry = (char*)malloc((j-2)*sizeof(char));

		    memset(*entry,'\0',j-2);
			

		    strcpy( *entry, aux );

		    free(aux);

		    status = 1;

		
		}
	    

	    }

	

	}

	
	    


    }

    
   

    return status;

}
