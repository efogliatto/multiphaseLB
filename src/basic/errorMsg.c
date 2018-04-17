#include <stdlib.h>
#include <stdio.h>
#include <errorMsg.h>


void errorMsg( char* msg ) {

    printf("\n   [ERROR]  %s\n\n", msg);

    exit(1);

}
