#include <dictIO.h>
#include <io.h>
#include <basic.h>
#include <stdlib.h>
#include <readVectorFromEnsight.h>


uint readVectorFromEnsight( latticeMesh* mesh, scalar*** field, char* fname ) {
    
    
    unsigned int status = 0;
    
    

    // Open file

    char name[200];

    sprintf(name, "lattice.%s_%d", fname, timeToIndex(mesh->time.current));

    MPI_File file;

    MPI_File_open( MPI_COMM_WORLD, name, MPI_MODE_RDONLY, MPI_INFO_NULL, &file );
    


    // Allocate space
        
    *field = matrixDoubleAlloc(mesh->mesh.nPoints, 3, 0);

    float *auxField = (float*)malloc( mesh->mesh.nPoints * sizeof(float) );




    // Set Offset

    MPI_Offset offset = 240*sizeof(char) + sizeof(int);

    uint i,j;

    for(i = 0 ; i < mesh->parallel.pid ; i++ ) {

	offset += 3*mesh->parallel.nodesPerPatch[i] * sizeof(float);

	offset += 160*sizeof(char) + sizeof(int);

    }

    MPI_File_seek(file, offset, MPI_SEEK_SET);



    
    // Read Array

    MPI_Status st;

    for( j = 0 ; j < 3 ; j++) {

	MPI_File_read(file, auxField, mesh->mesh.nPoints, MPI_FLOAT, &st);

	for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {

	    field[0][i][j] = (scalar)auxField[i];

	}
    
	MPI_Barrier(MPI_COMM_WORLD);

    }
    
    MPI_File_close(&file);

    free(auxField);



    if( (int)st._ucount/sizeof(float) == mesh->mesh.nPoints ) {

	status = 1;
	
    }

    
    
    return status;


}




/* // ASCII Version */

/* uint readVectorFromEnsight( latticeMesh* mesh, scalar*** field, char* fname ) { */
    
    
/*     unsigned int status = 0; */
    

/*     // Open file */

/*     char name[200]; */

/*     sprintf(name, "lattice.%s_%d", fname, timeToIndex(mesh->time.current)); */

/*     FILE* file = fopen( name, "r" ); */

/*     testFile(file, name); */


    
/*     // Allocate space */
    
/*     *field = matrixDoubleAlloc(mesh->mesh.nPoints, 3, 0); */




/*     // Find "part" definition */

/*     rewind(file); */

/*     uint find = 0; */

/*     char word[100];     */

/*     while(  find == 0  ) { */

/* 	status = fscanf(file,"%s",word); */
	
/*     	if( status != EOF ) { */
	
/*     	    if( strcmp(word, "part") == 0 ) { */

/*     	    	status = fscanf(file,"%s",word); */

/*     	    	if( atoi(word) == mesh->parallel.pid + 1 ) { */

/*     	    	    find = 1; */

/*     	    	} */

/*     	    } */

/*     	} */

/* 	else { */

/* 	    find = 1; */

/* 	} */
	
/*     } */


/*     // "coordinates" */
    
/*     status = fscanf(file,"%s",word); */

    


/*     // Read values */

/*     uint i,j; */

/*     float value; */

/*     for( j = 0 ; j < 3 ; j++ ) { */
    
/* 	for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) { */

/* 	    status = fscanf(file, "%f", &value); */

/* 	    field[0][i][j] = (scalar)value; */

/* 	} */

/*     } */
    
    
/*     fclose( file ); */

   

    
/*     return status; */

/* } */
