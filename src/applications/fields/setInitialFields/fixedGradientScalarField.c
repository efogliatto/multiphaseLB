#include <dictIO.h>
#include <latticeMesh.h>
#include <stdlib.h>
#include <stdio.h>
#include <basic.h>

void fixedGradientScalarField( latticeMesh* mesh, scalar** field, char* fname ) {


    // Allocate memory
    
    *field = (scalar*)malloc( mesh->mesh.nPoints * sizeof(scalar) );


    
    // Look for values. field = \vec{a} * \vec{x} + b

    char* aux;

    scalar b = 0;

    scalar* a;

    uint status,
	n;


    // Read b
    
    if(  vstring(&aux, "%s/internalField/offset", fname)  )    
	status = lookUpScalarEntry("start/initialFields", aux, 0, &b);


    // Read a
    
    if(  vstring(&aux, "%s/internalField/grad", fname)  )
	status = lookUpVectorEntry("start/initialFields", aux, &a, &n);

    


    if (status) {}
    
    
    uint i, j;

    scalar dot;

    for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {

	dot = 0;
	
	for ( j = 0 ; j < 3 ; j++ ) {

	    dot += a[j] * mesh->mesh.points[i][j];	   

	}

	field[0][i] = b + dot;

    }
    
    free(aux);

    free(a);

}
