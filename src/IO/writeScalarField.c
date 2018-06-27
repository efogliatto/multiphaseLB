/* #include <latticeMesh.h> */
/* #include <stdio.h> */
/* #include <stdlib.h> */
#include <writeScalarField.h>
#include <asciiRaw.h>
#include <binaryRaw.h>
#include <pvtu.h>


void writeScalarField( char* fname, scalar* field, latticeMesh* mesh ) {

    
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

	
    }

    
}
