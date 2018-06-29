#include <io.h>
#include <stdlib.h>
#include <readScalarFromEnsight.h>

uint readScalarFromEnsight( latticeMesh* mesh, scalar** field, char* fname ) {

    
    unsigned int status = 0;

    
    // Open file

    char name[200];

    sprintf(name, "lattice.%s%d", fname, timeToIndex(mesh->time.current));

    FILE* file = fopen( name, "r" );


    
    // Allocate space
        
    *field = (scalar*)malloc( mesh->mesh.nPoints * sizeof(scalar) );



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

    	field[0][i] = (scalar)value;

    }
    
    
    fclose( file );

    
    
    return status;

}