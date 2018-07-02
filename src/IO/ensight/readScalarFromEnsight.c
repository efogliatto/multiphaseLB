#include <io.h>
#include <stdlib.h>
#include <readScalarFromEnsight.h>
#include <timeToIndex.h>
#include <basic.h>

uint readScalarFromEnsight( latticeMesh* mesh, scalar** field, char* fname ) {

    
    unsigned int status = 0;

    
    // Open file

    char name[200];

    sprintf(name, "lattice.%s_%d", fname, timeToIndex(mesh->time.current));

    FILE* file = fopen( name, "r" );

    testFile(file, name);


    
    // Allocate space
        
    *field = (scalar*)malloc( mesh->mesh.nPoints * sizeof(scalar) );



    // Find "part" definition

    rewind(file);
    
    uint find = 0;

    char word[100];    

    while(  find == 0  ) {

	status = fscanf(file,"%s",word);
	
    	if( status != EOF ) {
	
    	    if( strcmp(word, "part") == 0 ) {

    	    	status = fscanf(file,"%s",word);

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
    
    status = fscanf(file,"%s",word);



    
    // Read values

    uint i;

    float value;
    
    for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {

    	status = fscanf(file, "%f", &value);

    	field[0][i] = (scalar)value;

    }
    
    
    fclose( file );

    
    
    return status;

}
