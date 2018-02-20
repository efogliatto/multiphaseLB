#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>

void bounceBack( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int bid ) {

    unsigned int i, k;
    

    // Move over boundary elements
    
    for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) {

	int id = mesh->mesh.bd.bdPoints[bid][i];

	
	// Move over lattice velocities
	
	for( k = 0 ; k < mesh->mesh.Q ; k++ ) {

	    if ( mesh->mesh.nb[id][k] == -1 ) {

		field->value[id][k] = field->value[id][mesh->lattice.reverse[k]];

	    }


	    // Correction for velocities lying on face
	    
	    else {

		if( (mesh->lattice.Q == 9) ) {

		    /* if( ( mesh->mesh.nb[id][k] == 1 )  ||  ( mesh->mesh.nb[id][k] == 2 )  ||  ( mesh->mesh.nb[id][k] == 3 )  ||  ( mesh->mesh.nb[id][k] == 4 )  ) { */

		    /* 	field->value[id][k] = 0.5 * field->value[id][k]  +  0.5 * field->value[id][mesh->lattice.reverse[k]]; */
		
		    /* 	field->value[id][mesh->lattice.reverse[k]] = field->value[id][k]; */

		    /* } */

		}

	    }

	}
	

    }

}
