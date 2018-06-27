#include <latticeMesh.h>
#include <stdio.h>
#include <stdlib.h>
#include <writeArrayToAsciiRaw.h>

void writeArrayToAsciiRaw( char* fname, scalar** field, latticeMesh* mesh, const uint vsize ) {

    
    FILE *outFile;

    char fileName[100];


    sprintf(fileName, "processor%d/%d/%s", mesh->parallel.pid, mesh->time.current, fname);

    outFile = fopen(fileName, "w");
    

	
    uint ii, jj;
    
    for( ii = 0 ; ii < mesh->mesh.nPoints ; ii++ ) {

	for( jj = 0 ; jj < vsize ; jj++ ) {
	
	    fprintf(outFile, "%g ", field[ii][jj]);

	}

	fprintf(outFile,"\n");
	
    }


    fclose(outFile);


}
