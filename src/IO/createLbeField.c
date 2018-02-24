#include <createLbeField.h>
#include <readLbeField.h>
#include <basic.h>


void createLbeField( struct latticeMesh* mesh, struct lbeField* field, char* fname ) {

    
    if(mesh->parallel.pid == 0) {

	printf("\nReading field %s\n",fname);

    }
    

    unsigned int status = readLbeField( mesh, field, fname);

    
    if( status == 0 ) {

	char msg[100];

	sprintf(msg, "Unable to read field %s",fname);
	
    	errorMsg( msg );
	
    }
    

}
