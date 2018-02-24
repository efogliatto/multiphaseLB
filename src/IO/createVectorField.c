#include <createVectorField.h>
#include <readVectorField.h>
#include <basic.h>


void createVectorField( struct latticeMesh* mesh, double*** field, unsigned int vsize, char* fname ) {

    
    if(mesh->parallel.pid == 0) {

	printf("\nReading field %s\n",fname);

    }
    

    unsigned int status = readVectorField( mesh, field, vsize, fname);

    
    if( status == 0 ) {

	char msg[100];

	sprintf(msg, "Unable to read field %s",fname);
	
    	errorMsg( msg );
	
    }
    

}
