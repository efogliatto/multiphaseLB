#include <writeVectorField.h>
#include <basic.h>
#include <asciiRaw.h>
#include <binaryRaw.h>
#include <pvtu.h>
#include <ensight.h>

void writeVectorField( char* fname, scalar** field, latticeMesh* mesh, const uint vsize ) {

    
    switch( mesh->time.data ) {

	
    case asciiRaw:

	writeArrayToAsciiRaw( fname, field, mesh, vsize );

	break;


    case binaryRaw:

	writeArrayToBinaryRaw( fname, field, mesh, vsize );

	break;
	
	
    case pvtu:

	writeArrayToPvtu( fname, field, mesh, vsize );

	break;


    case ensight:

	if( vsize == 3 ) {

	    writeVectorToEnsight( fname, field, mesh );

	}

	else {

	    writeLbeFieldToEnsight( fname, field, mesh );

	}

	break;	
	
    }

    
}
