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



double lookUpDouble( char* fileName, char* entry, double df ) {


    /* uint lsize; */

    double val = df;

    /* char** list = lookUpEntry(fileName,entry,&lsize); */


    /* if ( lsize != 0 ) { */

    /* 	char *ptr; */
	
    /* 	val = strtod( list[0], &ptr); */

    /* } */

    return val;
    

}
