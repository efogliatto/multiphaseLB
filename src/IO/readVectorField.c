#include <readVectorField.h>
#include <asciiRaw.h>
#include <binaryRaw.h>
#include <pvtu.h>
#include <ensight.h>

uint readVectorField( latticeMesh* mesh, scalar*** field, unsigned int vsize, char* fname ) {
    
    
    unsigned int status = 0;
    

    switch( mesh->time.data ) {

	
    case asciiRaw:

	status = readArrayFromAsciiRaw( mesh, field, vsize, fname);

	break;


    case binaryRaw:

	status = readArrayFromBinaryRaw( mesh, field, vsize, fname);

	break;
	

    case pvtu:

	status = readArrayFromPvtu( mesh, field, vsize, fname);

	break;


    case ensight:

	if( vsize == 3 ) {
	
	    status = readVectorFromEnsight( mesh, field, fname );

	}

	else {

	    status = readLbeFieldFromEnsight( mesh, field, fname );

	}

	break;	

	
    }
    
    
    return status;

}
