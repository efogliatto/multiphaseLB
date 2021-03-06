#include <io.h>
#include <stdlib.h>
#include <readLbeFieldFromEnsight.h>
#include <basic.h>

uint readLbeFieldFromEnsight( latticeMesh* mesh, scalar*** field, char* fname ) {

    
    uint status = 0;

    uint k;


    // Allocate space
    
    *field = matrixDoubleAlloc(mesh->mesh.nPoints, mesh->lattice.Q, 0);

    float *auxField = (float*)malloc( mesh->mesh.nPoints * sizeof(float) );

    
    
    for( k = 0 ; k < mesh->lattice.Q ; k++ ) {
    
    
	// Open file

	char name[200];

	sprintf(name, "lattice.%s%d_%d", fname, k, timeToIndex(mesh->time.current));

	MPI_File file;

	MPI_File_open( MPI_COMM_WORLD, name, MPI_MODE_RDONLY, MPI_INFO_NULL, &file );




	// Set Offset

	MPI_Offset offset = 240*sizeof(char) + sizeof(int);

	uint i;

	for(i = 0 ; i < mesh->parallel.pid ; i++ ) {

	    offset += mesh->parallel.nodesPerPatch[i] * sizeof(float);

	    offset += 160*sizeof(char) + sizeof(int);

	}

	MPI_File_seek(file, offset, MPI_SEEK_SET);



    
	// Read Array

	MPI_Status st;

	MPI_File_read(file, auxField, mesh->mesh.nPoints, MPI_FLOAT, &st);

	for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {

	    field[0][i][k] = (scalar)auxField[i];

	}	
    
	MPI_Barrier(MPI_COMM_WORLD);
    
	MPI_File_close(&file);



	if( (int)st._ucount/sizeof(float) == mesh->mesh.nPoints ) {

	    status = 1;
	
	}


    }




    free(auxField);
    
    return status;

}




/* // ASCII Version */

/* uint readLbeFieldFromEnsight( latticeMesh* mesh, scalar*** field, char* fname ) { */

    
/*     uint status = 0; */

/*     uint k; */


/*     // Allocate space */
    
/*     *field = matrixDoubleAlloc(mesh->mesh.nPoints, mesh->lattice.Q, 0); */

    
    
/*     for( k = 0 ; k < mesh->lattice.Q ; k++ ) { */
    
    
/* 	// Open file */

/* 	char name[200]; */

/* 	sprintf(name, "lattice.%s%d_%d", fname, k, timeToIndex(mesh->time.current)); */

/* 	FILE* file = fopen( name, "r" ); */

/* 	testFile(file, name); */



/* 	// Find "part" definition */

/* 	rewind(file); */
    
/* 	uint find = 0; */

/* 	char word[100]; */

/* 	while(  find == 0  ) { */

/* 	    status = fscanf(file,"%s",word);  */
	    
/* 		if( status != EOF ) { */
	
/* 		    if( strcmp(word, "part") == 0 ) { */

/* 		    	status = fscanf(file,"%s",word); */

/* 		    	if( atoi(word) == mesh->parallel.pid + 1 ) { */

/* 		    	    find = 1; */

/* 		    	} */

/* 		    } */

/* 		} */

/* 		else { */

/* 		    find = 1; */

/* 		} */
	
/* 	} */


/* 	// "coordinates" */
    
/* 	status = fscanf(file,"%s",word); */



    
/* 	// Read values */

/* 	uint i; */

/* 	float value; */
    
/* 	for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) { */

/* 		status = fscanf(file, "%f", &value); */

/* 		field[0][i][k] = (scalar)value; */

/* 	} */
    
    
/* 	fclose( file ); */


/*     } */
    
    
/*     return status; */

/* } */
