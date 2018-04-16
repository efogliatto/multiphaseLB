#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned int tokenize( char* src, char ***dest, unsigned int* n ) {

    
    unsigned int status = 0;


    // Count number of / ocurrences

    unsigned int count = 0,
	i;

    for( i = 0 ; i < (int)strlen(src) ; i++ ) {

	if( src[i] == '/' ) {

	    count++;

	}

    }



    // (Re)Allocate memory for dest

    *dest = (char**)malloc( (count+1) * sizeof(char*) );

    for( i = 0 ; i < (count+1) ; i++ ) {

    	(*dest)[i] = (char*)malloc( strlen(src) * sizeof(char) );

	memset((*dest)[i], '\0', strlen(src));

    }




    // Copy strings between tokens

    char *partial;

    for( i = 0 ; i < count ; i++ ) {
    
	partial = strchr(src, '/');

	strncpy( (*dest)[i], src, strlen(src) - strlen(partial));

	src = partial + 1;

    }


    // Copy last string
    
    strcpy( (*dest)[count], src );

    *n = count + 1;
    
    status = 1;

    

    return status;
    
}
