#include <io.h>
#include <stdlib.h>
#include <readScalarFromEnsight.h>
#include <timeToIndex.h>
#include <basic.h>

uint readScalarFromEnsight( latticeMesh* mesh, scalar** field, char* fname ) {

    
    unsigned int status = 0;
    


    // Non paralel

    if( mesh->parallel.worldSize == 1 ) {


	// Open file

	char name[200];

	sprintf(name, "lattice.%s_%d", fname, timeToIndex(mesh->time.current));

	FILE* file = fopen( name, "r" );

	testFile(file, name);

	fseek (file, 240*sizeof(char) + sizeof(int), SEEK_SET);


	
        // Allocate space
        
	*field = (scalar*)malloc( mesh->mesh.nPoints * sizeof(scalar) );

	float* auxField = (float*)malloc( mesh->mesh.nPoints * sizeof(float) );


	// Read array
	
	status = fread( auxField, sizeof(float), mesh->mesh.nPoints, file );


	// Copy to field array
	
	uint i;
	
	for(i = 0 ; i < mesh->mesh.nPoints ; i++) {

	    field[0][i] = (scalar)auxField[i];	    
	    
	}


	free(auxField);

	fclose(file);
	

    }



    else {

    

	// Open file

	char name[200];

	sprintf(name, "lattice.%s_%d", fname, timeToIndex(mesh->time.current));

	MPI_File file;

	MPI_File_open( MPI_COMM_WORLD, name, MPI_MODE_RDONLY, MPI_INFO_NULL, &file );
    


	// Allocate space
        
	*field = (scalar*)malloc( mesh->mesh.nPoints * sizeof(scalar) );




	// Set Offset

	MPI_Offset offset = 240*sizeof(char) + sizeof(int);

	uint i;

	for(i = 0 ; i < mesh->parallel.pid ; i++ ) {

	    offset += mesh->parallel.nodesPerPatch[i] * sizeof(float);

	    offset += 160*sizeof(char) + sizeof(int);

	}

	MPI_File_seek(file, offset, MPI_SEEK_SET);



    
	// Read Array

	float* auxField = (float*)malloc( mesh->mesh.nPoints * sizeof(float) );
	
	MPI_Status st;

	MPI_File_read(file, auxField, mesh->mesh.nPoints, MPI_FLOAT, &st);

	for(i = 0 ; i < mesh->mesh.nPoints ; i++) {

	    field[0][i] = (scalar)auxField[i];	    
	    
	}	
    
	MPI_Barrier(MPI_COMM_WORLD);
    
	MPI_File_close(&file);

	free(auxField);
    

	if( (int)st._ucount/sizeof(float) == mesh->mesh.nPoints ) {

	    status = 1;
	
	}


    }
    
    
    return status;

}




/* // ASCII Version */

/* uint readScalarFromEnsight( latticeMesh* mesh, scalar** field, char* fname ) { */

    
/*     unsigned int status = 0; */

    
/*     // Open file */

/*     char name[200]; */

/*     sprintf(name, "lattice.%s_%d", fname, timeToIndex(mesh->time.current)); */

/*     FILE* file = fopen( name, "r" ); */

/*     testFile(file, name); */


    
/*     // Allocate space */
        
/*     *field = (scalar*)malloc( mesh->mesh.nPoints * sizeof(scalar) ); */



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

/*     uint i; */

/*     float value; */
    
/*     for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) { */

/*     	status = fscanf(file, "%f", &value); */

/*     	field[0][i] = (scalar)value; */

/*     } */
    
    
/*     fclose( file ); */

    
    
/*     return status; */

/* } */
