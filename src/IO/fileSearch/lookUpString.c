/*

  Return string from file

  Tokenizes entry and returns elements as string

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



char* lookUpString( char* fileName, char* entry ) {


    uint lsize;


    char** list = lookUpEntry(fileName,entry,&lsize);

    char* val = (char*)malloc( 100 * sizeof(char) );

    if ( lsize != 0 ) {

    	strcpy(val, list[0]);

    }

    return val;
    

}
