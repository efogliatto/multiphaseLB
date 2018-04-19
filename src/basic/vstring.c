#include <vstring.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


unsigned int vstring( char** strp, const char* fmt, ... ) {

    unsigned int status = 0;


    // Work with arguments

    va_list valist;

    va_start( valist, fmt );


    printf(fmt,valist);
    
    
    // Compute size needed and allocate memory

    size_t strl = snprintf(NULL, 0, fmt, valist) + 1;

    /* printf("%d\n",(int)strl); */

    char* aux = (char*)malloc( (strl+1) * sizeof(char) );

    memset(strp, '\0', strl);


    // Print fmt

    /* strl = snprintf(aux, strl, fmt, valist); */

    /* printf("%s\n",aux); */
    

    va_end(valist);


    return status;

}
