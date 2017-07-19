#include <stdlib.h>
#include <stdio.h>
#include <entryList.h>

unsigned int entryIsPresent( char* fileName, char* entry ) {

    char bdl[100][100];

    unsigned int ls = 0;
    
    unsigned int status = entryList( fileName, entry, bdl, &ls );
    
    if (status) {}

    return ls;

}
