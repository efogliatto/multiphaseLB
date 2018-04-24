#include <dictIO.h>
#include <io.h>
#include <latticeMesh.h>
#include <stdlib.h>
#include <stdio.h>
#include <basic.h>


void sphereBoundedScalarField( latticeMesh* mesh, double** field, char* fname ) {


    // Allocate memory
    
    *field = (double*)malloc( mesh->mesh.nPoints * sizeof(double) );


    
    // Look for values

    char* aux;

    double in = 0,
	out = 0;

    double* centre;

    double radius;

    unsigned int status,
	n;

    
    // Centre
    
    if(  vstring(&aux, "%s/internalField/centre", fname)  )
	status = lookUpVectorEntry("start/initialFields", aux, &centre, &n);

    

    // Radius

    char* ins;
    
    if(  vstring(&ins, "%s/internalField/radius", fname)  )    
	status = lookUpScalarEntry("start/initialFields", ins, 0, &radius);
    

    // Inside value
    
    if(  vstring(&ins, "%s/internalField/inside", fname)  )    
	status = lookUpScalarEntry("start/initialFields", ins, 0, &in);



    // Outside value
    
    if(  vstring(&ins, "%s/internalField/outside", fname)  )    
	status = lookUpScalarEntry("start/initialFields", ins, 0, &out);

    
    
    if (status) {}
    
    
    uint ii;

    for( ii = 0 ; ii < mesh->mesh.nPoints ; ii++ ) {

	double r = ( mesh->mesh.points[ii][0] - centre[0] )  *  ( mesh->mesh.points[ii][0] - centre[0] ) +
	    ( mesh->mesh.points[ii][1] - centre[1] )  *  ( mesh->mesh.points[ii][1] - centre[1] ) + 
	    ( mesh->mesh.points[ii][2] - centre[2] )  *  ( mesh->mesh.points[ii][2] - centre[2] );

	if( r < radius * radius ) {
	
	    field[0][ii] = in;

	}

	else {

	    field[0][ii] = out;

	}

    }
    

    free(aux);

    free(centre);

}
