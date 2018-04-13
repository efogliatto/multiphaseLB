/*

  Return entry list from file

  return value
  0: entry not found
  1: entry was found

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokenize.h>


unsigned int entryList( char* fileName, char* entry, char list[][100], unsigned int* lsize ) {


    unsigned int retval = 0;

    
    // Open file and look for embraced entry

    FILE* file = fopen( fileName, "r" );

    if(file == NULL) {

	printf("\n [ERROR]   Unable to open file %s\n\n", fileName);

	exit(0);

    }


    // Go to begining
    rewind(file);


    // Read file word by word and add to array
    // This is implemented due to initial errors when trying to use this function multiple times

    uint fsize = 0;

    char aux[100];

    while( fscanf(file,"%s",aux) == 1 ) {
	
	fsize++;
	
    }


    // Go to begining
    rewind(file);




   
   


    char** fileContent = (char**)malloc( fsize * sizeof(char*) );

    unsigned int i,
	status;

    for( i = 0 ; i < fsize ; i++ ) {

	fileContent[i] = (char*)malloc( 100 * sizeof(char) );

	status = fscanf(file,"%s",fileContent[i]);
	
    }

    if(status) {}




      
    // Move until find entry followed by {

    unsigned int find = 0;

    i = 0;
    
    while(  ( find == 0 )   &&   ( i < (fsize-1))  ) {

	
	// Entry is found
	
	if( strcmp(fileContent[i],entry) == 0 ) {

	    
	    // Check if next character is {
	    
	    if( strcmp(fileContent[i+1],"{") == 0 ) {

		find = 1;

		i++;

	    }

	}

	i++;

    }

    

    // Read until corresponding } is found

    // bcount++ if { is found.
    // bcount-- if } is found.

    unsigned int bcount = 1;
    
    unsigned int nl = 0;

    
    while(   ( bcount != 0 )   &&   ( (i+nl) < (fsize -1) )   ){

	if( strcmp( fileContent[i+nl], "{" ) == 0 ) {

	    bcount++;

	}

	else {

	    if( strcmp( fileContent[i+nl], "}" ) == 0 ) {

		bcount--;

	    }

	}


	if( bcount != 0 ) {
	    
	    nl++;

	}

	else {

	    retval = 1;

	}

    }

       
    
   
    fclose(file);


    

    // Copy strings to list

    *lsize = nl;
    
    unsigned int j;

    for( j = 0 ; j < nl ; j++ ) {

    	strcpy( list[j], fileContent[i+j] );

	retval = 1 ;

    }
    

    


    // Deallocate arrays

    for( i = 0 ; i < fsize ; i++ ) {

    	free( fileContent[i] );

    }

    free( fileContent );




    
    return retval;
    
    

}
