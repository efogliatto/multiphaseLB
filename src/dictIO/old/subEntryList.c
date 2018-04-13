/*

  Return entry sub list from array list

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenize.h>


unsigned int subEntryList( char entryList[][100], unsigned int elsize, char* entry, char subList[][100], unsigned int* lsize ) {


    unsigned int retval = 0;
    

    // Move in entryList until entry with opening brace

    unsigned int i,
    	find;
    
    
    i = 0;

    find = 0;
    
    while(   ( i < (elsize-1) )   &&   ( find == 0 )   ) {

    	if(   ( strcmp(entryList[i], entry) == 0 )   &&   ( strcmp(entryList[i+1], "{") == 0 )   ) {

    	    find = 1;

    	    i++;

    	}

    	i++;

    }




    

    // Find corresponding }

    unsigned int bcount = 1,
    	j = i;

    while(   ( j < elsize )   &&   ( bcount != 0 )   )  {

    	if ( strcmp(entryList[j], "{") == 0 ) {

    	    bcount++;

    	}

    	else {

    	    if ( strcmp(entryList[j], "}") == 0 ) {

    		bcount--;

    	    }

    	}

    	j++;

    }


    j--;
    
    



    // Resize sublist and copy

    if( bcount == 0 ) {
    
	*lsize = j - i;

	unsigned int k;

	for( k = 0 ; k < (j-i) ; k++ ) {

	    strcpy( subList[k], entryList[i + k] );

	}

	retval = 1;

    }


    
    
    return retval;

}
