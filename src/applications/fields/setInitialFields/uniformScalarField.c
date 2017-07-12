#include <io.h>
#include <latticeMesh.h>
#include <stdlib.h>
#include <stdio.h>

void uniformScalarField( struct latticeMesh* mesh, double** field, char* fname ) {


    // Allocate memory
    
    *field = (double*)malloc( mesh->mesh.nPoints * sizeof(double) );


    
    // Look for values

    char aux[100];

    double fval = 0;
    
    sprintf(aux, "%s/internalField/value", fname);

    unsigned int status = lookUpDouble("start/initialFields", aux, &fval, 0);


    if (status) {}
    
    
    uint ii;

    for( ii = 0 ; ii < mesh->mesh.nPoints ; ii++ ) {

	field[0][ii] = fval;

    }
    


}



/* field = (double*)malloc( mesh.mesh.nPoints * sizeof(double) ); */
		
		
/* sprintf(fname, "%s/internalField/value", vtk.scalarFields[fid] ); */

/* status = lookUpDouble("start/initialFields", fname, &fval, 0); */


/* uint ii; */

/* for( ii = 0 ; ii < mesh.mesh.nPoints ; ii++ ) { */

/*     field[ii] = fval; */

/* } */
