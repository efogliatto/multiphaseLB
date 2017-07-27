#include <latticeMesh.h>

double vectorDivergence( struct latticeMesh* mesh, double** v, unsigned int id ) {

    double div,
	aux = 0,
	dot = 0;

    // Only for D2Q9 case

    unsigned int j,
	k,
	nb,
	find = 0;

    for( k = 1 ; k < 5 ; k++ ) {


	nb = mesh->mesh.nb[id][ mesh->lattice.reverse[k] ];

	if ( nb != -1 ) {

	    dot = 0;
	    
	    for( j = 0 ; j < 2 ; j++ ) {

		dot += v[nb][j] * mesh->lattice.vel[k][j];

	    }

	    aux += dot;

	}

	else {

	    find = 1;

	}

    }
    


    if ( find == 0  ) {

	div = aux;

    }

    else {

	div = 0;

    }

    
    return div;

}
