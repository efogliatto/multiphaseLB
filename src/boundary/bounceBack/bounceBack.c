#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>
#include <bounceBack.h>


void bounceBack( latticeMesh* mesh, macroFields* mfields, scalar** field, uint bid ) {

    uint i, k;
    

    // Move over boundary elements
    
    for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) {

	int id = mesh->mesh.bd.bdPoints[bid][i];

	
	// Move over lattice velocities
	
	for( k = 0 ; k < mesh->mesh.Q ; k++ ) {

	    if ( mesh->mesh.nb[id][k] == -1 ) {

		field[id][k] = field[id][mesh->lattice.reverse[k]];

	    }


	    // Correction for velocities lying on face
	    
	    else {

		if( mesh->mesh.nb[id][mesh->lattice.reverse[k]] != -1 ) {
		
		    if( (mesh->lattice.Q == 9) ) {

			if( ( k == 1 )  ||  ( k == 2 )  ||  ( k == 3 )  ||  ( k == 4 )  ) {

			    field[id][k] = 0.5 * field[id][k]  +  0.5 * field[id][mesh->lattice.reverse[k]];
		
			    field[id][mesh->lattice.reverse[k]] = field[id][k];

			}

		    }



		    else {

			if( (mesh->lattice.Q == 15) ) {

			    if( ( k == 1 )  ||  ( k == 2 )  ||  ( k == 3 )  ||  ( k == 4 )   ||  ( k == 5 )   ||  ( k == 6 ) ) {

				field[id][k] = 0.5 * field[id][k]  +  0.5 * field[id][mesh->lattice.reverse[k]];
		
				field[id][mesh->lattice.reverse[k]] = field[id][k];

			    }

			}

		    }

		    

		}

	    }

	}
	

    }

}
