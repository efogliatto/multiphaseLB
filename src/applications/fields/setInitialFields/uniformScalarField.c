#include <dictIO.h>
#include <latticeMesh.h>
#include <stdlib.h>
#include <stdio.h>
#include <basic.h>

void uniformScalarField( latticeMesh* mesh, double** field, char* fname ) {


    // Allocate memory
    
    *field = (double*)malloc( mesh->mesh.nPoints * sizeof(double) );


    
    // Look for values

    char* aux;

    double fval = 0;    

    unsigned int status = 0;

    if( vstring(&aux, "%s/internalField/value", fname)  )
	status = lookUpScalarEntry("start/initialFields", aux, 0, &fval);


    if (status) {   
    
	uint ii;

	for( ii = 0 ; ii < mesh->mesh.nPoints ; ii++ ) {

	    field[0][ii] = fval;

	}    

    }

    /* // Read boundary information */


    /* // Move over boundary names */

    /* char bd[100]; */
    
    /* unsigned int bid; */

    /* double bdval = fval; */

    /* for( bid = 0 ; bid < mesh->mesh.bd.nbd ; bid++ ) { */

    /* 	sprintf(bd, "%s/boundaryField/%s", fname, mesh->mesh.bd.bdNames[bid]); */

    /* 	status = lookUpDouble("start/initialFields", bd, &bdval, fval); */


    /* 	unsigned int j; */

    /* 	for( j = 0 ; j < mesh->mesh.bd.nbdelem[bid] ; j++ ) { */

    /* 	    field[0][ mesh->mesh.bd.bdPoints[bid][j] ] = bdval; */

    /* 	} */

    /* } */



    

    

}



/* field = (double*)malloc( mesh.mesh.nPoints * sizeof(double) ); */
		
		
/* sprintf(fname, "%s/internalField/value", vtk.scalarFields[fid] ); */

/* status = lookUpDouble("start/initialFields", fname, &fval, 0); */


/* uint ii; */

/* for( ii = 0 ; ii < mesh.mesh.nPoints ; ii++ ) { */

/*     field[ii] = fval; */

/* } */
