/*

  Return entry sub list from array sub list

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenize.h>


char** singleEntryList( char** subEntryList, char* entry, unsigned int* lsize, unsigned int ssize ) {

    
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

    *lsize = j - i;
    
    char** subList = (char**)malloc( (j-i) * sizeof(char*) );

    unsigned int k;

    for( k = 0 ; k < (j-i) ; k++ ) {

    	subList[k] = (char*)malloc( 100 * sizeof(char) );


	// Remove extra characters	

    	strcpy( subList[k], subEntryList[i + k] );

	subList[k] = strtok( subList[k], ";" );

	subList[k] = strtok( subList[k], "(" );

	subList[k] = strtok( subList[k], ")" );

    }

    
    return subList;
    
    
    
}
