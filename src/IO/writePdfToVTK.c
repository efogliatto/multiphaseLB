#include <latticeMesh.h>
#include <stdio.h>
#include <stdlib.h>


void writePdfToVTK( char* fname, double** field, struct latticeMesh* mesh ) {

    FILE *outFile;

    char fileName[100];

    // Open file
    sprintf(fileName, "processor%d/%d/fields.vtu", mesh->parallel.pid, mesh->time.current);

    outFile = fopen(fileName, "a");
    


    // Print header
    fprintf(outFile, "        <DataArray type=\"Float32\" Name=\"%s\"  NumberOfComponents=\"%d\" format=\"ascii\">\n", fname, mesh->mesh.Q);

    // Print field
    unsigned int i,j;
    for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {
	fprintf(outFile, "          ");
	for( j = 0 ; j < mesh->mesh.Q ; j++ ) {
	    fprintf(outFile, "%f ", field[i][j]);
	}
	fprintf(outFile, "\n");
    }

    fprintf(outFile, "        </DataArray>\n");


    fclose(outFile);


}
