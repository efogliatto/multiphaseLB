#include <latticeMesh.h>
#include <basic.h>
#include <writeLbeFieldToEnsight.h>
#include <writeScalarToEnsight.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <timeToIndex.h>


void writeLbeFieldToEnsight( char* fname, scalar** field, latticeMesh* mesh ) {


    // Non paralel but distributed

    if( mesh->parallel.worldSize == 1 ) {


	char* cname;
    
	uint status, k;

	for( k = 0 ; k < mesh->lattice.Q ; k++ ) {

	
	    status = vstring(&cname, "%s%d", fname, k);

	    if(status) {}
	

	
	    // Write field
    
	    FILE *outFile;

	    char fileName[100];

	    uint fcount = timeToIndex(mesh->time.current);

	    sprintf(fileName, "lattice.%s_%d", cname, fcount);
	    
    

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
	


    
	    uint i;

	    float value;
    
	    for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {

		value = (float)field[i][k];
	    
		fwrite( &value, sizeof(float), 1, outFile );
	
	    }


	    fclose(outFile);

	    free(msg);



	}

	free(cname);
	

    }

    
  

    
}




/* // ASCII VERSION */

/* void writeLbeFieldToEnsight( char* fname, scalar** field, latticeMesh* mesh ) { */


/*     // Receive flag from "previous" processor */

/*     int flag; */
    
/*     if(   ( mesh->parallel.pid != 0 )   &&  ( mesh->parallel.worldSize > 1 )   ) { */
    
/*     	MPI_Recv(&flag, 1, MPI_INT, mesh->parallel.pid-1, mesh->parallel.pid-1, MPI_COMM_WORLD, MPI_STATUS_IGNORE); */

/*     } */


    

/*     char* cname; */
    
/*     uint status, k; */

/*     for( k = 0 ; k < mesh->lattice.Q ; k++ ) { */

	
/* 	status = vstring(&cname, "%s%d", fname, k); */

/* 	if(status) {} */


/* 	/\* // Count file ocurrences *\/ */

/* 	/\* DIR *dir; *\/ */
    
/* 	/\* struct dirent *ent; *\/ */

/* 	/\* uint fcount = 0; *\/ */

/* 	/\* char name[256]; *\/ */

/* 	/\* sprintf(name,"lattice.%s",cname); *\/ */


/* 	/\* if ((dir = opendir (".")) != NULL) { *\/ */

/* 	/\*     while ((ent = readdir (dir)) != NULL) { *\/ */
	    
/* 	/\* 	if(strstr(ent->d_name, name) != NULL) { *\/ */

/* 	/\* 	    fcount++; *\/ */

/* 	/\* 	} *\/ */
	    
/* 	/\*     } *\/ */
	
/* 	/\*     closedir (dir); *\/ */
	
/* 	/\* } *\/ */




/* 	// Write field */
    
/* 	FILE *outFile; */

/* 	char fileName[100]; */

/* 	uint fcount = timeToIndex(mesh->time.current); */

/* 	sprintf(fileName, "lattice.%s_%d", cname, fcount); */

	

/* 	if( mesh->parallel.pid == 0 ) { */
	
/* 	    outFile = fopen(fileName, "w"); */

/* 	    testFile(outFile, fileName); */

/* 	    fprintf(outFile, "%s\n", cname); */

/* 	    fclose(outFile); */

/* 	} */


/* 	outFile = fopen(fileName, "a"); */

/* 	testFile(outFile, fileName); */

/* 	fprintf(outFile,"part\n"); */

/* 	fprintf(outFile,"%10d\n",mesh->parallel.pid+1); */

/* 	fprintf(outFile,"coordinates\n"); */

	
/* 	uint i; */
    
/* 	for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) { */
	
/* 	    fprintf(outFile, "%12.5e\n", field[i][k]); */
	
/* 	} */


/* 	fclose(outFile); */
	
	

/*     } */


/*     free(cname); */
    



/*     // Send flag to "next" processor */

/*     if(    ( mesh->parallel.worldSize > 1 )     &&    ( mesh->parallel.pid != mesh->parallel.worldSize - 1 )  ){ */
    
/*     	MPI_Send(&flag, 1, MPI_INT, mesh->parallel.pid+1, mesh->parallel.pid, MPI_COMM_WORLD); */

/*     } */
    
/* } */
