/*

  Return string from file

  Tokenizes entry and returns elements as string

 */


#include <lookUpEntry.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned int uint;


unsigned int lookUpString( char* fileName, char* entry, char string[] ) {


    uint retval = 0,
	ns,
	status;

    char aux[10][100];
    
    status = lookUpEntry( fileName, entry, aux, &ns);

    if (status) {

	strcpy(string, aux[0]);

	retval = 1;

    }
    
    
    return retval;
    

}
