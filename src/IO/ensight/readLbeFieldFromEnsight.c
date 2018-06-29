#include <io.h>
#include <stdlib.h>
#include <readLbeFieldFromEnsight.h>
#include <basic.h>

uint readLbeFieldFromEnsight( latticeMesh* mesh, scalar*** field, char* fname ) {

    
    uint status = 0;

    uint k;


    // Allocate space
    
    *field = matrixDoubleAlloc(mesh->mesh.nPoints, mesh->lattice.Q, 0);

    
    
    for( k = 0 ; k < mesh->lattice.Q ; k++ ) {
    
    
	// Open file

	char name[200];

	sprintf(name, "lattice.%s%d%d", fname, k, timeToIndex(mesh->time.current));

	FILE* file = fopen( name, "r" );



	// Find "part" definition

	rewind(file);
    
	uint find = 0;

	char word[100];

	while(  find == 0  ) {

		if( fscanf(file,"%s",word) != EOF ) {
	
		    if( strcmp(word, "part") == 0 ) {

		    	fscanf(file,"%s",word);

		    	if( atoi(word) == mesh->parallel.pid + 1 ) {

		    	    find = 1;

		    	}

		    }

		}

		else {

		    find = 1;

		}
	
	}


	// "coordinates"
    
	fscanf(file,"%s",word);



    
	// Read values

	uint i;

	float value;
    
	for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {

		status = fscanf(file, "%f", &value);

		field[0][i][k] = (scalar)value;

	}
    
    
	fclose( file );


    }
    
    
    return status;

}
