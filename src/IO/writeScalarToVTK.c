#include <latticeMesh.h>
#include <stdio.h>
#include <stdlib.h>

void writeScalarToVTK( char* fname, double* field, struct latticeMesh* mesh ) {

    FILE *outFile;

    char fileName[100];

    // Open file
    sprintf(fileName, "processor%d/%d/fields.vtu", mesh->parallel.pid, mesh->time.current);

    outFile = fopen(fileName, "a");
    


    // Print header
    fprintf(outFile, "        <DataArray type=\"Float32\" Name=\"%s\" format=\"ascii\">\n", fname);

    // Print field
    unsigned int i;
    
    for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {
	
	fprintf(outFile, "          %g\n", field[i]);
	
    }

    
    fprintf(outFile, "        </DataArray>\n");


    fclose(outFile);

}
