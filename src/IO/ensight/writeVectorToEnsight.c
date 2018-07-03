#include <latticeMesh.h>
#include <stdio.h>
#include <stdlib.h>
#include <writeVectorToEnsight.h>
#include <basic.h>
#include <dirent.h>
#include <string.h>
#include <timeToIndex.h>

void writeVectorToEnsight( char* fname, scalar** field, latticeMesh* mesh ) {

    

    // Non paralel but distributed

    if( mesh->parallel.worldSize == 1 ) {

	
	// Write field
    
	FILE *outFile;

	char fileName[100];

	uint fcount = timeToIndex(mesh->time.current);

	sprintf(fileName, "lattice.%s_%d", fname, fcount);
    

	// Header
	
	if( mesh->parallel.pid == 0 ) {
	
	    outFile = fopen(fileName, "wb");

	    testFile(outFile, fileName);

	    char* msg = (char*)malloc( 80*sizeof(char) );

	    memset(msg,'\0', 80);	

	    sprintf(msg, "%s", fname);

	    fwrite( msg, sizeof(char), 80, outFile );	  

	    fclose(outFile);

	    free(msg);

	}


	// Part description

	outFile = fopen(fileName, "ab");

	testFile(outFile, fileName);


	char* msg = (char*)malloc( 80*sizeof(char) );

	memset(msg,'\0', 80);	

	sprintf(msg, "part");
	
	fwrite( msg, sizeof(char), 80, outFile );


	
	uint pid = mesh->parallel.pid+1;

	fwrite( &pid, sizeof(int), 1, outFile );



	memset(msg,'\0', 80);	

	sprintf(msg, "coordinates");
	
	fwrite( msg, sizeof(char), 80, outFile );
	


    
	uint i,j;

	float value;

	for( j = 0 ; j < 3 ; j++ ) {
	
	    for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {

		value = (float)field[i][j];
	    
		fwrite( &value, sizeof(float), 1, outFile );
	
	    }

	}


	fclose(outFile);

	free(msg);
	

    }  

    


}





/* // ASCII Version */

/* void writeVectorToEnsight( char* fname, scalar** field, latticeMesh* mesh ) { */

    
/*     // Receive flag from "previous" processor */

/*     int flag; */
    
/*     if(   ( mesh->parallel.pid != 0 )   &&  ( mesh->parallel.worldSize > 1 )   ) { */
    
/*     	MPI_Recv(&flag, 1, MPI_INT, mesh->parallel.pid-1, mesh->parallel.pid-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE); */

/*     } */
    


/*     // Write field */
    
/*     FILE *outFile; */

/*     char fileName[100]; */

/*     uint fcount = timeToIndex(mesh->time.current); */

/*     sprintf(fileName, "lattice.%s_%d", fname, fcount); */
    

/*     if( mesh->parallel.pid == 0 ) { */
	
/* 	outFile = fopen(fileName, "w"); */

/* 	testFile(outFile, fileName);	 */

/* 	fprintf(outFile, "%s\n", fname); */

/* 	fclose(outFile); */
	
/*     } */



/*     outFile = fopen(fileName, "a"); */

/*     testFile(outFile, fileName); */

/*     fprintf(outFile,"part\n"); */

/*     fprintf(outFile,"%10d\n",mesh->parallel.pid+1); */

/*     fprintf(outFile,"coordinates\n"); */
	
/*     uint i,j; */

/*     for( j = 0 ; j < 3 ; j++ ) { */
    
/* 	for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) { */
	
/* 	    fprintf(outFile, "%12.5e\n", field[i][j]); */
	
/* 	} */

/*     } */


/*     fclose(outFile); */


    
/*     // Send flag to "next" processor */

/*     if(    ( mesh->parallel.worldSize > 1 )     &&    ( mesh->parallel.pid != mesh->parallel.worldSize - 1 )  ){ */
    
/*     	MPI_Send(&flag, 1, MPI_INT, mesh->parallel.pid+1, mesh->parallel.pid, MPI_COMM_WORLD); */

/*     } */

/* } */
