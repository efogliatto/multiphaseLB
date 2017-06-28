#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char** tokenize( char* str2, char token, uint* n ) {


    uint ntk = 0;

    char* next;
    
    char* curr = str2;

    char aux[100][100];

    char** str1;


    

    // Move between tokens. Find token occurrence and move pointer
    
    while ( (next = strchr(curr, token)) != NULL ) {

	// Copy to aux array
	strncpy( aux[ntk], curr, strlen(curr)-strlen(next) );
	
	ntk++;
	
	// Process curr to next-1
	curr = next + 1;
	
    }

    
    // Copy last entry if exists
    
    if( strlen(curr) != 0 ) {
	
	strcpy( aux[ntk], curr );

	ntk++;
	
    }

    *n = ntk;



    
    // Resize str1 and copy aux

    str1 = (char**)malloc( ntk * sizeof(char*) );

    uint i;

    for( i = 0 ; i < ntk ; i++) {

    	str1[i] = (char*)malloc( 100 * sizeof(char) );

    	strcpy( str1[i], aux[i] );

    }


    

    return str1;
    
}
