#include <writeVectorField.h>
#include <basic.h>
#include <math.h>
#include <asciiRaw.h>
#include <binaryRaw.h>
#include <pvtu.h>
#include <ensight.h>

void writeVectorField( char* fname, scalar** field, latticeMesh* mesh, const uint vsize ) {

    
    // First check for array sanity
    uint i, j;

    for( i = 0 ; i < mesh->mesh.nPoints ; i++) {

	for( j = 0 ; j < vsize ; j++) {

	    if( isnan(field[i][j]) ) {

		errorMsg("Floating point exception. NaN solution");

	    }

	}

    }

    
    
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
