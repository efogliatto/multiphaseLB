#include <dictIO.h>
#include <latticeMesh.h>
#include <stdlib.h>
#include <stdio.h>
#include <basic.h>
#include <math.h>

void tgProfileScalarField( latticeMesh* mesh, scalar** field, char* fname ) {


    // Allocate memory
    
    *field = (scalar*)malloc( mesh->mesh.nPoints * sizeof(scalar) );


    
    // Look for values. field = \vec{a} * \vec{x} + b

    char* aux;

    scalar rl = 0,
	rg = 0,
	z1 = 0,
	z2 = 0,
	W = 0;

    uint status;


    // Read rl
    
    if(  vstring(&aux, "%s/internalField/rl", fname)  )    
	status = lookUpScalarEntry("start/initialFields", aux, 0, &rl);


    // Read rg
    
    if(  vstring(&aux, "%s/internalField/rg", fname)  )    
	status = lookUpScalarEntry("start/initialFields", aux, 0, &rg);


    // Read W
    
    if(  vstring(&aux, "%s/internalField/W", fname)  )    
	status = lookUpScalarEntry("start/initialFields", aux, 0, &W);


    // Read z1
    
    if(  vstring(&aux, "%s/internalField/z1", fname)  )    
	status = lookUpScalarEntry("start/initialFields", aux, 0, &z1);


    // Read z2
    
    if(  vstring(&aux, "%s/internalField/z2", fname)  )    
	status = lookUpScalarEntry("start/initialFields", aux, 0, &z2);        
    

    if (status) {}


    
    
    uint i;

    scalar zz1, zz2;

    for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {

	zz1 = 2.0 * (mesh->mesh.points[i][2]-z1) / W;

	zz2 = 2.0 * (mesh->mesh.points[i][2]-z2) / W;

	field[0][i] = rg + (rl - rg) / 2.0 * (tanh(zz1) - tanh(zz2));

    }
    
    free(aux);

}
