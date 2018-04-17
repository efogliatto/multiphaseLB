#include <createScalarField.h>
#include <readScalarField.h>
#include <basic.h>


void createScalarField( latticeMesh* mesh, double** field, char* fname ) {

    
    if(mesh->parallel.pid == 0) {

	printf("\nReading field %s\n",fname);

    }
    

    unsigned int status = readScalarField( mesh, field, fname);

    
    if( status == 0 ) {

	char msg[100];

	sprintf(msg, "Unable to read field %s",fname);
	
    	errorMsg( msg );
	
    }
    

}
