#include <createScalarField.h>
#include <readScalarField.h>
#include <basic.h>


void createScalarField( latticeMesh* mesh, scalar** field, char* fname, fieldOpt options ) {


    uint status = 0,
	i;
    
    
    if(mesh->parallel.pid == 0) {

	printf("\nReading field %s\n",fname);

    }


    switch(options) {
    

	// Read field from fields.vtu
	
    case MUST_READ:
	
	status = readScalarField( mesh, field, fname );

    
	if( status == 0 ) {

	    char msg[100];

	    sprintf(msg, "Unable to read field %s",fname);
	
	    errorMsg( msg );
	
	}

	break;



	// Do not read field from file. Only allocate field

    case NO_READ:

	*field = (scalar*)malloc( mesh->mesh.nPoints * sizeof(scalar) );

	for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {

	    field[0][i] = 0;

	}

	break;

	
	

    }
    

}
