#include <stdio.h>
#include <stdlib.h>
#include <latticeMesh.h>
#include <lbeField.h>
#include <macroFields.h>
#include <liTempEquilibrium.h>
#include <liMRTEquilibrium.h>



void outflow(  latticeMesh* mesh,  macroFields* mfields,  double** field, unsigned int bid ) {


    unsigned int i, j, k;
    

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

	unsigned int ln = 0;

	for( k = 0 ; k < mesh->mesh.Q ; k++ ) {
	    
	    if(  (mesh->lattice.vel[k][0] == normal[0])  &&  (mesh->lattice.vel[k][1] == normal[1])  &&  (mesh->lattice.vel[k][2] == normal[2])  ) {	       
		
	    	ln = k;

	    }

	}
	
	

	// Interpolate missing components from neighbour in normal direction

	unsigned int neigh = mesh->mesh.nb[id][ln];

	if( neigh != -1 ) {

	    for( k = 0 ; k < mesh->mesh.Q ; k++ ) {

		if( mesh->mesh.nb[id][k] == -1 ) {
		
		    field->value[id][k] = field->value[neigh][k];

		}

	    }

	}
	

	

    }

}




/* void outflow( struct latticeMesh* mesh, struct macroFields* mfields, struct lbeField* field, unsigned int bid ) { */

/*     unsigned int i, j, k; */
    

/*     // Move over boundary elements */
    
/*     for( i = 0 ; i < mesh->mesh.bd.nbdelem[bid] ; i++ ) { */

/* 	int id = mesh->mesh.bd.bdPoints[bid][i]; */


/* 	// Move over principal directions only */

/* 	for( j = 1 ; j <= 4 ; j++ ) { */

	    
/* 	    // Copy from reverse point if neighbour is not present */
	    
/* 	    if( mesh->mesh.nb[id][j] == -1 ) { */


/* 		unsigned int nid = mesh->mesh.nb[id][ mesh->lattice.reverse[j] ]; */
		

/* 		// Move over lattice velocities and copy info */
	
/* 		for( k = 0 ; k < mesh->mesh.Q ; k++ ) { */

/* 		    field->value[id][k] = field->value[nid][k]; */

/* 		} */

		

/* 	    } */
	    
       

/* 	} */
	

/*     } */

/* } */
