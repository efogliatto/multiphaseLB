#include <string.h>
#include <stdio.h>

unsigned int bracedEntry( char* ename, char* content, char* entry ) {

    unsigned int status = 0;


    // Check ename + { ocurrence
    char *partial = strstr(content, ename);


    // Not wanted, but there can multiple entries (maybe nested)
    
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


	    j--;



	    // Copy if found

	    if( bcount == 0 ) {

	    	entry = (char*)malloc((j+1)*sizeof(char));

	    	strncpy( entry, &partial[1], j-1 );

	    	/* printf("%s\n",entry); */

		status = 1;
		
	    }
	    

	}

	

    }

    
   

    return status;

}
