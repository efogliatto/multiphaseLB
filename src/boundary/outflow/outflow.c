#include <stdio.h>
#include <stdlib.h>
#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>
#include <outflow.h>

void outflow( latticeMesh* mesh, macroFields* mfields, scalar** field, uint bid ) {


    uint i, j, k;
    

    // Move over boundary elements
    
    for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) {

	int id = mesh->mesh.bd.bdPoints[bid][i];


	// Check which is the normal direction, using unknown neighbours

	int normal[3] = {0,0,0};

	for( k = 0 ; k < mesh->mesh.Q ; k++ ) {

	    if( mesh->mesh.nb[id][ mesh->lattice.reverse[k] ] == -1 ) {

		for( j = 0 ; j < 3 ; j++ ) {

		    normal[j] += mesh->lattice.vel[k][j];

		}

	    }

	}

	for( j = 0 ; j < 3 ; j++ ) {

	    if( normal[j] != 0 ) {

		normal[j] = normal[j] / abs(normal[j]);

	    }

	}

	
	


	// Detect correspondence with lattice velocities

	uint ln = 0;

	for( k = 0 ; k < mesh->mesh.Q ; k++ ) {
	    
	    if(  (mesh->lattice.vel[k][0] == normal[0])  &&  (mesh->lattice.vel[k][1] == normal[1])  &&  (mesh->lattice.vel[k][2] == normal[2])  ) {	       
		
	    	ln = k;

	    }

	}
	
	

	// Interpolate missing components from neighbour in normal direction

	uint neigh = mesh->mesh.nb[id][ln];

	if( neigh != -1 ) {

	    for( k = 0 ; k < mesh->mesh.Q ; k++ ) {

		if( mesh->mesh.nb[id][k] == -1 ) {
		
		    field[id][k] = field[neigh][k];

		}

	    }

	}
	

	

    }

}
