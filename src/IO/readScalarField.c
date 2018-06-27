/* #include <io.h> */
/* #include <stdlib.h> */
#include <readScalarField.h>
#include <asciiRaw.h>
#include <binaryRaw.h>
#include <pvtu.h>

uint readScalarField( latticeMesh* mesh, scalar** field, char* fname ) {

    
    unsigned int status = 0;
    

    switch( mesh->time.data ) {

	
    case asciiRaw:

	status = readScalarFromAsciiRaw( mesh, field, fname);

	break;

	
    case binaryRaw:

	status = readScalarFromBinaryRaw( mesh, field, fname);

	break;
	

    case pvtu:

	status = readScalarFromPvtu( mesh, field, fname);

	break;	

	
    }

    
    return status;

}
