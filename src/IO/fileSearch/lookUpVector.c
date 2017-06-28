/*

  Return double from file

  Tokenizes entry and returns elements as double

 */


#include <tokenize.h>
#include <entryList.h>
#include <subEntryList.h>
#include <singleEntryList.h>
#include <lookUpEntry.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned int uint;



double* lookUpVector( char* fileName, char* entry, double df, unsigned int vs ) {


    uint lsize;

    double val = df;

    char** list = lookUpEntry(fileName,entry,&lsize);


    double* rval = (double*)malloc( lsize * sizeof(double) );
    
    
    if ( lsize == vs ) {

	uint i;

    	char *ptr;

	for( i = 0 ; i < lsize ; i++ ) {
	
	    val = strtod( list[i], &ptr);

	    rval[i] = val;

	}

    }

    else {

	printf("\n   [ERROR]   Ill defined entry %s. Dimension mismatch\n\n", entry);

	exit(1);

    }

    return rval;
    

}
