#include <dictIO.h>
#include <latticeMesh.h>
#include <stdlib.h>
#include <stdio.h>
#include <basic.h>


void boxBoundedScalarField( latticeMesh* mesh, scalar** field, char* fname ) {


    // Allocate memory
    
    *field = (scalar*)malloc( mesh->mesh.nPoints * sizeof(scalar) );


    
    // Look for values

    char* aux;

    scalar in = 0,
	out = 0;

    scalar* min;

    scalar* max;

    uint status = 0;

    

    // Min corner

    uint n;
    
    if(  vstring(&aux, "%s/internalField/minPoint", fname)  )
	status = lookUpVectorEntry("start/initialFields", aux, &min, &n);    


    // Max corner

    if(  vstring(&aux, "%s/internalField/maxPoint", fname)  )
	status = lookUpVectorEntry("start/initialFields", aux, &max, &n);
    

    
    // Inside value

    char* ins;
    
    if(  vstring(&ins, "%s/internalField/inside", fname)  )    
	status = lookUpScalarEntry("start/initialFields", ins, 0, &in);



    // Outside value

    if(  vstring(&ins, "%s/internalField/outside", fname)  )    
	status = lookUpScalarEntry("start/initialFields", ins, 0, &out);
    
    
    
    if (status) {}
    
    
    uint ii;

    for( ii = 0 ; ii < mesh->mesh.nPoints ; ii++ ) {


	if( ( min[0] <= mesh->mesh.points[ii][0] )   &&
	    ( max[0] >= mesh->mesh.points[ii][0] )   &&
	    ( min[1] <= mesh->mesh.points[ii][1] )   &&
	    ( max[1] >= mesh->mesh.points[ii][1] )   &&
	    ( min[2] <= mesh->mesh.points[ii][2] )   &&
	    ( max[2] >= mesh->mesh.points[ii][2] )  ) {
	
	    field[0][ii] = in;

	}

	else {

	    field[0][ii] = out;

	}

    }
    


    free(aux);

}
