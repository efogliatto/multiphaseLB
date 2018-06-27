/* #include <dictIO.h> */
/* #include <io.h> */
/* #include <basic.h> */
#include <readVectorField.h>
#include <asciiRaw.h>
#include <pvtu.h>

uint readVectorField( latticeMesh* mesh, scalar*** field, unsigned int vsize, char* fname ) {
    
    
    unsigned int status = 0;
    

    switch( mesh->time.data ) {

	
    case asciiRaw:

	status = readArrayFromAsciiRaw( mesh, field, vsize, fname);

	break;


    case pvtu:

	status = readArrayFromPvtu( mesh, field, vsize, fname);

	break;	

	
    }
    
    
    return status;

}
