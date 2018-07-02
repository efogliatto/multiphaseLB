#include <testFile.h>
#include <errorMsg.h>
#include <vstring.h>
#include <stdlib.h>

void testFile( FILE* fp, char* fileName ) {

    if(fp == NULL) {

	char* msg;
	    
	if(  vstring(&msg, "Unable to open file %s", fileName )  )
	    errorMsg(msg);

	free(msg);

    }


}
