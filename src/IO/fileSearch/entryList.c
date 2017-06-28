/*

  Return entry list from file

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenize.h>


char** entryList( char* fileName, char* entry, uint* lsize ) {


    // Open file and look for embraced entry

    FILE* file = fopen( fileName, "r" );

    if(file == NULL) {

	printf("\n [ERROR]   Unable to open file %s\n\n", fileName);

	exit(0);

    }
    

    
    char auxList[100][100];

    char aux[100];



    
    // Move until find entry followed by {

    uint find = 0;

    uint status;

    while( find == 0 ) {
	
	status = fscanf(file,"%s",aux);

	// Bad reading
	if(status == 0) {

	    find = 1;

	}

	else {

	    // Entry is found
	    if( strcmp(aux,entry) == 0 ) {

		// Check if next character is {
		status = fscanf(file,"%s",aux);

		if( strcmp(aux,"{") == 0 ) {

		    find = 1;

		}

	    }

	}

    }




    // Read until corresponding } is found

    // bcount++ if { is found.
    // bcount-- if } is found.
    uint bcount = 1;
    uint nl = 0;

    while( bcount != 0 ) {

	status = fscanf(file,"%s",aux);

	if( status == 0 ) {

	    bcount = 0;

	}

	else {

	    if( strcmp(aux,"{") == 0 ) {

		bcount++;

	    }

	    else {

		if( strcmp(aux,"}") == 0 ) {

		    bcount--;

		}

	    }


	    if( bcount != 0 ) {
	    
		// Copy to list
		strcpy( auxList[nl], aux );

		nl++;

	    }

	    

	}

    }

       
    
    

    fclose(file);



    // Copy strings to list

    *lsize = nl;
    
    char** list = (char**)malloc( nl * sizeof(char*) );


    uint i;

    for( i = 0 ; i < nl ; i++ ) {

	list[i] = (char*)malloc( 100 * sizeof(char) );

	strcpy( list[i], auxList[i] );

    }
    


    

    return list;

}
