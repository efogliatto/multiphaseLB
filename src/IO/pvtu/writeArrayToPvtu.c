#include <latticeMesh.h>
#include <stdio.h>
#include <stdlib.h>
#include <writeArrayToPvtu.h>

void writeArrayToPvtu( char* fname, scalar** field, latticeMesh* mesh, const uint vsize ) {

    
    FILE *outFile;

    char fileName[100];

    // Open file
    sprintf(fileName, "processor%d/%d/fields.vtu", mesh->parallel.pid, mesh->time.current);

    outFile = fopen(fileName, "a");
    


    // Print header
    fprintf(outFile, "        <DataArray type=\"Float32\" Name=\"%s\"  NumberOfComponents=\"%d\" format=\"ascii\">\n", fname, vsize);

    
    // Print field

    uint i,j;
    
    for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {
	
	fprintf(outFile, "          ");
	
	for( j = 0 ; j < vsize ; j++ ) {
	    
	    fprintf(outFile, "%g ", field[i][j]);
	    
	}
	
	fprintf(outFile, "\n");
    }


    
    fprintf(outFile, "        </DataArray>\n");

    fclose(outFile);


}
