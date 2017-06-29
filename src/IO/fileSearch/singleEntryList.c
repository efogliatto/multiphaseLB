/*

  Return entry sub list from array sub list

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenize.h>


unsigned int singleEntryList( char subEntryList[][100], unsigned int ssize, char* entry, char subList[][100], unsigned int* lsize ) {


    unsigned int retval = 0;
    
    
    // Move in subEntryList until entry with opening brace

    unsigned int i,
    	find;

    
    i = 0;

    find = 0;
    
    while(   ( i < (ssize-1) )   &&   ( find == 0 )   ) {

    	if(   ( strcmp(subEntryList[i], entry) == 0 )   ) {

    	    find = 1;

    	}

    	i++;

    }


    
    

    // Find ";" token

    unsigned int j = i;

    find = 0;

    while(   ( j < ssize )   &&   ( find == 0 )   ) {

    	if( strchr(subEntryList[j],';') != NULL ) {

    	    find = 1;
	    
    	}
	
    	j++;

    }


    
    // Resize sublist and copy
    
    if( find == 1 ) {    

	*lsize = j - i;
    
	unsigned int k;

	char* aux = (char*)malloc( 100 * sizeof(char) );
	
	for( k = 0 ; k < (j-i) ; k++ ) {

	    
	    // Remove extra characters
	    
	    strcpy( aux, subEntryList[i + k] );

	    aux = strtok( aux, ";" );

	    aux = strtok( aux, "(" );

	    aux = strtok( aux, ")" );

	    
	    strcpy( subList[k], aux );
	    
	}

	retval = 1;

	/* free( aux ); */

    }



    
    return retval;
    
    
    
}
