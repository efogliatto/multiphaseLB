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









    // Parallel version

    else {

	
	MPI_Barrier(MPI_COMM_WORLD);
	

        // Open File
    
	char fileName[100];

	uint fcount = timeToIndex(mesh->time.current);

	sprintf(fileName, "lattice.%s_%d", fname, fcount);


	MPI_File file;

	MPI_File_open( MPI_COMM_WORLD, fileName, MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &file );

	

	// Header
	
	if( mesh->parallel.pid == 0 ) {

	    char* msg = (char*)malloc( 80*sizeof(char) );

	    memset(msg,'\0', 80);

	    sprintf(msg, "%s", fname);

	    MPI_File_write(file, msg, 80, MPI_CHAR, MPI_STATUS_IGNORE);

	    free(msg);

	}


	MPI_Barrier(MPI_COMM_WORLD);



       



	// Set Offset

	uint offset = 80*sizeof(char);

	uint i,j;

	for(i = 0 ; i < mesh->parallel.pid ; i++ ) {

	    offset += 3 * mesh->parallel.nodesPerPatch[i] * sizeof(float);

	    offset += 160*sizeof(char) + sizeof(int);

	}

	MPI_File_seek(file, offset, MPI_SEEK_SET);



	// Write "part" description

	char* msg = (char*)malloc( 80*sizeof(char) );

	memset(msg,'\0', 80);

	sprintf(msg, "part");

	MPI_File_write(file, msg, 80, MPI_CHAR, MPI_STATUS_IGNORE);
	
	
	uint pid = mesh->parallel.pid+1;

	MPI_File_write(file, &pid, 1, MPI_INT, MPI_STATUS_IGNORE);


	
	memset(msg,'\0', 80);

	sprintf(msg, "coordinates");

	MPI_File_write(file, msg, 80, MPI_CHAR, MPI_STATUS_IGNORE);

	free(msg);
	

	
	// Write Array

	float *auxField = (float*)malloc( mesh->mesh.nPoints * sizeof(float) );

	for( j = 0 ; j < 3 ; j++) {

	    for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {

		auxField[i] = (float)field[i][j];

	    }

	    MPI_File_write(file, auxField, mesh->mesh.nPoints, MPI_FLOAT, MPI_STATUS_IGNORE);

	}

	free(auxField);



	// Close file

	MPI_File_close(&file);


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

/* 	testFile(outFile, fileName); */

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
