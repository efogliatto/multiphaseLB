#include <createLbeField.h>
#include <readLbeField.h>
#include <basic.h>


void createLbeField( latticeMesh* mesh, lbeField* field, char* fname, fieldOpt options ) {

    
    if(mesh->parallel.pid == 0) {

	printf("\nReading field %s\n",fname);

    }
    

    uint status = readLbeField( mesh, field, fname);

    
    if( status == 0 ) {

	char msg[100];

	sprintf(msg, "Unable to read field %s",fname);
	
    	errorMsg( msg );
	
    }
    

}
