#include <createVectorField.h>
#include <readVectorField.h>
#include <basic.h>


void createVectorField( latticeMesh* mesh, scalar*** field, uint vsize, char* fname, fieldOpt options ) {

    
    if(mesh->parallel.pid == 0) {

	printf("\nReading field %s\n",fname);

    }
    

    uint status = readVectorField( mesh, field, vsize, fname);

    
    if( status == 0 ) {

	char msg[100];

	sprintf(msg, "Unable to read field %s",fname);
	
    	errorMsg( msg );
	
    }
    

}
