#include <updateCaseFile.h>
#include <stdlib.h>
#include <stdio.h>

void updateCaseFile( const latticeMesh* mesh ) {

    if(mesh->parallel.pid == 0) {
    
	// Write current time step

	FILE* file = fopen("lbm.case","a");

	fprintf(file, "%.1f ", (float)mesh->time.current);

	fclose(file);





	

    }

}
