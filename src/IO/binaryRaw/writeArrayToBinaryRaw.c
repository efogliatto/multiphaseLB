#include <latticeMesh.h>
#include <stdio.h>
#include <stdlib.h>
#include <writeArrayToBinaryRaw.h>
#include <basic.h>


void writeArrayToBinaryRaw( char* fname, scalar** field, latticeMesh* mesh, const uint vsize ) {

    
    FILE *outFile;

    char fileName[100];


    // Create folder

    sprintf(fileName, "mkdir -p processor%d/%d", mesh->parallel.pid, mesh->time.current);
    
    unsigned int status = system(fileName);



    // Write field

    if ( status == 0 ) {
    
	sprintf(fileName, "processor%d/%d/%s", mesh->parallel.pid, mesh->time.current, fname);

	outFile = fopen(fileName, "wb");
    

	
	uint i, j;

	float value;
    
	for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {

	    for( j = 0 ; j < vsize ; j++ ) {

		value = (float)field[i][j];
		
		fwrite( &value, sizeof(float), 1, outFile );

	    }
	    
	}


	fclose(outFile);

    }



    else {

	errorMsg("Unable to create time folder");

    }


}
