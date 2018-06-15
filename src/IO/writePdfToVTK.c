#include <latticeMesh.h>
#include <stdio.h>
#include <stdlib.h>
#include <writePdfToVTK.h>

void writePdfToVTK( char* fname, scalar** field, latticeMesh* mesh ) {

	    

    
    
    FILE *outFile;

    char fileName[100];

    // Open file
    sprintf(fileName, "processor%d/%d/fields.vtu", mesh->parallel.pid, mesh->time.current);

    outFile = fopen(fileName, "a");
    


    // Print header
    fprintf(outFile, "        <DataArray type=\"Float32\" Name=\"%s\"  NumberOfComponents=\"%d\" format=\"ascii\">\n", fname, mesh->mesh.Q);

    // Print field
    uint i,j;
    
    for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {
	
	fprintf(outFile, "          ");
	
	for( j = 0 ; j < mesh->mesh.Q ; j++ ) {
	    
	    fprintf(outFile, "%g ", field[i][j]);
	    
	}
	
	fprintf(outFile, "\n");
    }

    fprintf(outFile, "        </DataArray>\n");


    fclose(outFile);




    // Write debug info

    if( mesh->time.debug != 0 ) {


	sprintf(fileName, "processor%d/%d/%s", mesh->parallel.pid, mesh->time.current, fname);

	outFile = fopen(fileName, "w");
    
	fprintf(outFile, "%d\n", mesh->mesh.nPoints);


	
	uint ii, jj;
    
	for( ii = 0 ; ii < mesh->mesh.nPoints ; ii++ ) {

	    for( jj = 0 ; jj < mesh->mesh.Q ; jj++ ) {
	
		fprintf(outFile, "%g ", field[ii][jj]);

	    }

	    fprintf(outFile,"\n");
	
	}


	fclose(outFile);


    }
    

}
