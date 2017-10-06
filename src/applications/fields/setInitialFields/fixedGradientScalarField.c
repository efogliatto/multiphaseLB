#include <io.h>
#include <latticeMesh.h>
#include <stdlib.h>
#include <stdio.h>

void fixedGradientScalarField( struct latticeMesh* mesh, double** field, char* fname ) {


    // Allocate memory
    
    *field = (double*)malloc( mesh->mesh.nPoints * sizeof(double) );


    
    // Look for values. field = \vec{a} * \vec{x} + b

    char aux[100];

    double b = 0;

    double a[3];


    // Read b
    
    sprintf(aux, "%s/internalField/b", fname);
    
    unsigned int status = lookUpDouble("start/initialFields", aux, &b, 0);


    // Read a
    
    sprintf(aux, "%s/internalField/a", fname);

    status = lookUpVector("start/initialFields", aux, a, 3);


    if (status) {}
    
    
    uint i, j;

    for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {

    	field[0][i] = b;
	
	for ( j = 0 ; j < 3 ; j++ ) {

	    field[0][i] = field[0][i] + a[j] * mesh->mesh.points[i][j];

	}

    }
    
    

}
