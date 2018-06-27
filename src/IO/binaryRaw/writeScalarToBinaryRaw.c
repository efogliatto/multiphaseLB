#include <latticeMesh.h>
#include <stdio.h>
#include <stdlib.h>
#include <writeScalarToBinaryRaw.h>
#include <basic.h>

void writeScalarToBinaryRaw( char* fname, scalar* field, latticeMesh* mesh ) {

    FILE *outFile;

    char fileName[100];


    // Create folder

    sprintf(fileName, "mkdir -p processor%d/%d", mesh->parallel.pid, mesh->time.current);
    
    unsigned int status = system(fileName);


    
    // Write field

    if ( status == 0 ) {

    
	sprintf(fileName, "processor%d/%d/%s", mesh->parallel.pid, mesh->time.current, fname);

	outFile = fopen(fileName, "wb");

	unsigned int i;

	float value;

	for( i = 0 ; i < mesh->mesh.nPoints ; i++) {

	    value = (float)field[i];
	    
	    fwrite( &value, sizeof(float), 1, outFile );

	}

	fclose(outFile);


    }



    else {

	errorMsg("Unable to create time folder");

    }


}
