#include <io.h>
#include <latticeMesh.h>
#include <stdlib.h>
#include <stdio.h>


void sphereBoundedScalarField( struct latticeMesh* mesh, double** field, char* fname ) {


    // Allocate memory
    
    *field = (double*)malloc( mesh->mesh.nPoints * sizeof(double) );


    
    // Look for values

    char aux[100];

    double in = 0,
	out = 0;

    double centre[3], radius;


    // Centre
    
    sprintf(aux, "%s/internalField/centre", fname);

    unsigned int status = lookUpVector("start/initialFields", aux, centre, 3);

    

    // Radius

    char ins[100];
    
    sprintf(ins, "%s/internalField/radius", fname);
    
    status = lookUpDouble("start/initialFields", ins, &radius, 0);
    

    // Inside value
    
    sprintf(ins, "%s/internalField/inside", fname);
    
    status = lookUpDouble("start/initialFields", ins, &in, 0);



    // Outside value
    
    sprintf(ins, "%s/internalField/outside", fname);
    
    status = lookUpDouble("start/initialFields", ins, &out, 0);

    
    
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
    


}
