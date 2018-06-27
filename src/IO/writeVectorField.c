/* #include <latticeMesh.h> */
/* #include <stdio.h> */
/* #include <stdlib.h> */
#include <writeVectorField.h>
#include <basic.h>
#include <asciiRaw.h>
#include <binaryRaw.h>
#include <pvtu.h>

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


    default:

	errorMsg("Data format not recognized");

	
    }

    
}
