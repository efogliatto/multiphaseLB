#include <writeScalarField.h>
#include <basic.h>
#include <math.h>
#include <asciiRaw.h>
#include <binaryRaw.h>
#include <pvtu.h>
#include <ensight.h>


void writeScalarField( char* fname, scalar* field, latticeMesh* mesh ) {


    // First check for array sanity
    uint i;

    for( i = 0 ; i < mesh->mesh.nPoints ; i++) {

	if( isnan(field[i]) ) {

	    errorMsg("Floating point exception. NaN solution");

	}

    }
    
    
    switch( mesh->time.data ) {

	
    case asciiRaw:

	writeScalarToAsciiRaw( fname, field, mesh );

	break;

	
    case binaryRaw:

	writeScalarToBinaryRaw( fname, field, mesh );

	break;
	

    case pvtu:

	writeScalarToPvtu( fname, field, mesh );

	break;


    case ensight:

	writeScalarToEnsight( fname, field, mesh );

	
    }

    
}
