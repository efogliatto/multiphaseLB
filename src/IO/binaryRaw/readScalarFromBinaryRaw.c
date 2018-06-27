#include <io.h>
#include <stdlib.h>
#include <readScalarFromBinaryRaw.h>

uint readScalarFromBinaryRaw( latticeMesh* mesh, scalar** field, char* fname ) {

    
    unsigned int status = 0;
    

    // Open file

    char name[200];

    sprintf(name, "processor%d/%d/%s", mesh->parallel.pid, mesh->time.current, fname);

    FILE* file = fopen( name, "rb" );


    
    // Allocate space
        
    *field = (scalar*)malloc( mesh->mesh.nPoints * sizeof(scalar) );



    // Read values

    uint i;

    float value;
    
    for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {

	status = fread( &value, sizeof(float), 1, file );

	field[0][i] = (scalar)value;

    }    
    
    
    fclose( file );

    
    
    return status;

}
