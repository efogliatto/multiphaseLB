#include <dictIO.h>
#include <io.h>
#include <basic.h>
#include <readArrayFromAsciiRaw.h>


uint readArrayFromAsciiRaw( latticeMesh* mesh, scalar*** field, unsigned int vsize, char* fname ) {
    
    
    unsigned int status = 0;
    

    // Open file

    char name[200];

    sprintf(name, "processor%d/%d/%s", mesh->parallel.pid, mesh->time.current, fname);

    FILE* file = fopen( name, "r" );
   


    // Allocate space
    
    *field = matrixDoubleAlloc(mesh->mesh.nPoints, vsize, 0);

    
    // Read values

    uint i,j;

    float value;

    for ( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {

	for ( j = 0 ; j < vsize ; j++ ) {

	    status = fscanf(file, "%f", &value);
		
	    field[0][i][j] = (scalar)value;

	}

    }

    
    
    fclose( file );

    
    return status;

}
