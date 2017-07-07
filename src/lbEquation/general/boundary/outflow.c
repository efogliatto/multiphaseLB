#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>

void outflow( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int bid ) {

    unsigned int i, j, k;
    

    // Move over boundary elements
    
    for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) {

	int id = mesh->mesh.bd.bdPoints[bid][i];


	// Move over principal directions only

	for( j = 1 ; j <= 4 ; j++ ) {

	    
	    // Copy from reverse point if neighbour is not present
	    
	    if( mesh->mesh.nb[id][j] == -1 ) {


		unsigned int nid = mesh->mesh.nb[id][ mesh->lattice.reverse[j] ];
		

		// Move over lattice velocities and copy info
	
		for( k = 0 ; k < mesh->mesh.Q ; k++ ) {

		    field->value[id][k] = field->value[nid][k];

		}

		

	    }
	    
       

	}
	

    }

}
