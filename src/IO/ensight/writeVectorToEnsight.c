#include <latticeMesh.h>
#include <stdio.h>
#include <stdlib.h>
#include <writeVectorToEnsight.h>
#include <basic.h>
#include <dirent.h>
#include <string.h>

void writeVectorToEnsight( char* fname, scalar** field, latticeMesh* mesh ) {


    // Count file ocurrences

    DIR *dir;
    
    struct dirent *ent;

    uint fcount = 0;

    char name[256];

    sprintf(name,"lattice.%s",fname);


    if ((dir = opendir (".")) != NULL) {

    	while ((ent = readdir (dir)) != NULL) {
	    
    	    if(strstr(ent->d_name, name) != NULL) {

    		fcount++;

    	    }
	    
    	}
	
    	closedir (dir);
	
    }




    // Write field
    
    FILE *outFile;

    char fileName[100];
      

    if( mesh->parallel.pid == 0 ) {

	sprintf(fileName, "lattice.%s%d", fname, fcount);
	
	outFile = fopen(fileName, "w");

	fprintf(outFile, "%s\n", fname);

	fclose(outFile);

	fcount++;

    }


    sprintf(fileName, "lattice.%s%d", fname, fcount-1);

    outFile = fopen(fileName, "a");

    fprintf(outFile,"part\n");
    fprintf(outFile,"%10d\n",mesh->parallel.pid+1);
    fprintf(outFile,"coordinates\n");
	
    uint i,j;

    for( j = 0 ; j < 3 ; j++ ) {
    
	for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {
	
	    fprintf(outFile, "%12.5e\n", field[i][j]);
	
	}

    }


    fclose(outFile);



}
