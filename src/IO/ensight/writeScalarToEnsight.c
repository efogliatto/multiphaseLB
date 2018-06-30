#include <latticeMesh.h>
#include <stdio.h>
#include <stdlib.h>
#include <writeScalarToEnsight.h>
#include <basic.h>
#include <dirent.h>
#include <string.h>

void writeScalarToEnsight( char* fname, scalar* field, latticeMesh* mesh ) {


    // Receive flag from "previous" processor

    int flag;
    
    if(   ( mesh->parallel.pid != 0 )   &&  ( mesh->parallel.worldSize > 1 )   ) {
    
    	MPI_Recv(&flag, 1, MPI_INT, mesh->parallel.pid-1, mesh->parallel.pid-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    }


    

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
	
    uint ii;
    
    for( ii = 0 ; ii < mesh->mesh.nPoints ; ii++ ) {
	
    	fprintf(outFile, "%12.5e\n", field[ii]);
	
    }


    fclose(outFile);



    // Send flag to "next" processor

    if(    ( mesh->parallel.worldSize > 1 )     &&    ( mesh->parallel.pid != mesh->parallel.worldSize - 1 )  ) {
    
    	MPI_Send(&flag, 1, MPI_INT, mesh->parallel.pid+1, mesh->parallel.pid, MPI_COMM_WORLD);

    }
    

}
