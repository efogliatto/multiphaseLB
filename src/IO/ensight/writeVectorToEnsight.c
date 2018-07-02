#include <latticeMesh.h>
#include <stdio.h>
#include <stdlib.h>
#include <writeVectorToEnsight.h>
#include <basic.h>
#include <dirent.h>
#include <string.h>
#include <timeToIndex.h>

void writeVectorToEnsight( char* fname, scalar** field, latticeMesh* mesh ) {

    
    // Receive flag from "previous" processor

    int flag;
    
    if(   ( mesh->parallel.pid != 0 )   &&  ( mesh->parallel.worldSize > 1 )   ) {
    
    	MPI_Recv(&flag, 1, MPI_INT, mesh->parallel.pid-1, mesh->parallel.pid-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    }
    

    
    /* // Count file ocurrences */

    /* DIR *dir; */
    
    /* struct dirent *ent; */

    /* uint fcount = 0; */

    /* char name[256]; */

    /* sprintf(name,"lattice.%s",fname); */


    /* if ((dir = opendir (".")) != NULL) { */

    /* 	while ((ent = readdir (dir)) != NULL) { */
	    
    /* 	    if(strstr(ent->d_name, name) != NULL) { */

    /* 		fcount++; */

    /* 	    } */
	    
    /* 	} */
	
    /* 	closedir (dir); */
	
    /* } */




    // Write field
    
    FILE *outFile;

    char fileName[100];

    uint fcount = timeToIndex(mesh->time.current);

    sprintf(fileName, "lattice.%s_%d", fname, fcount);
    

    if( mesh->parallel.pid == 0 ) {
	
	outFile = fopen(fileName, "w");

	testFile(outFile, fileName);	

	fprintf(outFile, "%s\n", fname);

	fclose(outFile);
	
    }



    outFile = fopen(fileName, "a");

    testFile(outFile, fileName);

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


    
    // Send flag to "next" processor

    if(    ( mesh->parallel.worldSize > 1 )     &&    ( mesh->parallel.pid != mesh->parallel.worldSize - 1 )  ){
    
    	MPI_Send(&flag, 1, MPI_INT, mesh->parallel.pid+1, mesh->parallel.pid, MPI_COMM_WORLD);

    }

}
