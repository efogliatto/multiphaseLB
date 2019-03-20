#include <dictIO.h>
#include <io.h>
#include <latticeMesh.h>
#include <stdlib.h>
#include <stdio.h>
#include <basic.h>


void sphereBoundedVectorField( latticeMesh* mesh, scalar** field, char* fname ) {


   
    // Look for values

    char* aux;

    scalar* in;

    scalar* out;

    scalar* centre;

    scalar radius;

    uint status,
    	n;

    
    // Centre
    
    if(  vstring(&aux, "%s/internalField/centre", fname)  )
    	status = lookUpVectorEntry("start/initialFields", aux, &centre, &n);


    // Inside value
    
    if(  vstring(&aux, "%s/internalField/inside", fname)  )
    	status = lookUpVectorEntry("start/initialFields", aux, &in, &n);


    // Outside value
    
    if(  vstring(&aux, "%s/internalField/outside", fname)  )
    	status = lookUpVectorEntry("start/initialFields", aux, &out, &n);
    

    // Radius

    char* ins;
    
    if(  vstring(&ins, "%s/internalField/radius", fname)  )
    	status = lookUpScalarEntry("start/initialFields", ins, 0, &radius);
    

    
    
    if (status) {}
    
    
    uint ii;

    for( ii = 0 ; ii < mesh->mesh.nPoints ; ii++ ) {

    	scalar r = ( mesh->mesh.points[ii][0] - centre[0] )  *  ( mesh->mesh.points[ii][0] - centre[0] ) +
    	    ( mesh->mesh.points[ii][1] - centre[1] )  *  ( mesh->mesh.points[ii][1] - centre[1] ) +
    	    ( mesh->mesh.points[ii][2] - centre[2] )  *  ( mesh->mesh.points[ii][2] - centre[2] );

    	if( r < radius * radius ) {

    	    field[ii][0] = in[0];
    	    field[ii][1] = in[1];
    	    field[ii][2] = in[2];

    	}

    	else {

    	    field[ii][0] = out[0];
    	    field[ii][1] = out[1];
    	    field[ii][2] = out[2];

    	}

    }
    

    free(aux);

    free(centre);

    free(in);

    free(out);

}
