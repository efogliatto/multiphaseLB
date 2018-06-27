#include <latticeMesh.h>
#include <stdio.h>
#include <stdlib.h>
#include <writeScalarToAsciiRaw.h>
#include <basic.h>

void writeScalarToAsciiRaw( char* fname, scalar* field, latticeMesh* mesh ) {

    FILE *outFile;

    char fileName[100];


    // Create folder

    sprintf(fileName, "mkdir -p processor%d/%d", mesh->parallel.pid, mesh->time.current);
    
    unsigned int status = system(fileName);


    
    // Write field

    if ( status == 0 ) {

    
	sprintf(fileName, "processor%d/%d/%s", mesh->parallel.pid, mesh->time.current, fname);

	outFile = fopen(fileName, "w");
    
	
	uint ii;
    
	for( ii = 0 ; ii < mesh->mesh.nPoints ; ii++ ) {
	
	    fprintf(outFile, "%g\n", field[ii]);
	
	}


	fclose(outFile);


    }



    else {

	errorMsg("Unable to create time folder");

    }


}
