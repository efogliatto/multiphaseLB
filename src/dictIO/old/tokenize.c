#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void tokenize( char* str2, char token, char str1[][100], unsigned int* n ) {


    uint ssize = strlen(str2);
   
    uint ntk = 0,
	i,
	j;


    // Move over string

    j = 0;
    
    for( i = 0 ; i < ssize ; i++ ) {

	if( str2[i] == token ) {

	    uint k;

	    for(k = j ; k < i ; k++ ) {

		str1[ntk][k - j] = str2[k];

	    }


	    j = i+1;

	    ntk++;

	}

    }

    if(j < ssize) {

    	uint k;

    	for(k = j ; k < ssize ; k++ ) {

    	    str1[ntk][k - j] = str2[k];

    	}

    	ntk++;

    }


    *n = ntk;
    












    /* uint ntk = 0; */

    /* char* next;     */

    /* char* curr = str2; */
    
    /* char aux[100][100]; */


   

    /* // Move between tokens. Find token occurrence and move pointer */
    
    /* while ( (next = strchr(curr, token)) != NULL ) { */

    /* 	// Copy to aux array */
    /* 	strncpy( aux[ntk], curr, strlen(curr)-strlen(next) ); */
	
    /* 	ntk++; */
	
    /* 	// Process curr to next-1 */
    /* 	curr = next + 1; */
	
    /* } */

    
    /* // Copy last entry if exists */
    
    /* if( strlen(curr) != 0 ) { */
	
    /* 	strcpy( aux[ntk], curr ); */

    /* 	ntk++; */
	
    /* } */

    /* *n = ntk; */



    
    /* // Resize str1 and copy aux */

    /* /\* str1 = (char**)malloc( ntk * sizeof(char*) ); *\/ */

    /* uint i; */

    /* for( i = 0 ; i < ntk ; i++) { */

    /* 	/\* str1[i] = (char*)malloc( 100 * sizeof(char) ); *\/ */

    /* 	/\* strcpy( str1[i], aux[i] ); *\/ */

    /* 	sprintf(str1[i],"%s",aux[i]); */

    /* } */


   
    

    
}
