/*

  Return entry sub list from array list

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenize.h>


char** subEntryList( char** entryList, char* entry, unsigned int* lsize, unsigned int elsize ) {


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

    while(   ( j < (elsize-1) )   &&   ( bcount != 0 )   )  {

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




    



    // Resize sublist and copy

    *lsize = j - i;
    
    char** subList = (char**)malloc( (j-i) * sizeof(char*) );

    unsigned int k;

    for( k = 0 ; k < (j-i) ; k++ ) {

    	subList[k] = (char*)malloc( 100 * sizeof(char) );

    	strcpy( subList[k], entryList[i + k] );

    }

    
    return subList;

}
