#include <dictIO.h>
#include <latticeMesh.h>
#include <stdlib.h>
#include <stdio.h>
#include <basic.h>

void fixedGradientScalarField( latticeMesh* mesh, double** field, char* fname ) {


    // Allocate memory
    
    *field = (double*)malloc( mesh->mesh.nPoints * sizeof(double) );


    
    // Look for values. field = \vec{a} * \vec{x} + b

    char* aux;

    double b = 0;

    double* a;

    unsigned int status,
	n;


    // Read b
    
    if(  vstring(&aux, "%s/internalField/b", fname)  )    
	status = lookUpScalarEntry("start/initialFields", aux, 0, &b);


    // Read a
    
    if(  vstring(&aux, "%s/internalField/a", fname)  )
	status = lookUpVectorEntry("start/initialFields", aux, &a, &n);


    if (status) {}
    
    
    uint i, j;

    for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {

    	field[0][i] = b;
	
	for ( j = 0 ; j < 3 ; j++ ) {

	    field[0][i] = field[0][i] + a[j] * mesh->mesh.points[i][j];

	}

    }
    
    

}
