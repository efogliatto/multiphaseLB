#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;


void periodicY( int** neigh, unsigned int nx, unsigned int ny, unsigned int Q, int** bmap, int* btid ) {


    btid[0] = (ny-2);
    btid[1] = (ny-2);
    btid[2] = nx;
    btid[3] = nx;


    int j,
	velId;


    // Move over Y-boundary points
    for( j = 0 ; j < nx ; j++ ) {

	bmap[2][j] = j;
	
	bmap[3][j] = j + (nx-1)*ny;


    	// Assign periodic neighbours
    	for( velId = 0 ; velId < Q ; velId++ ) {

    	    if(neigh[j][velId] == -1) {

    		neigh[j][velId] = neigh[ j + (nx-1)*ny ][velId];

    	    }

    	    if(neigh[ j + (nx-1)*ny ][velId] == -1) {

    		neigh[ j + (nx-1)*ny ][velId] = neigh[j][velId];

    	    }
	    
    	}	

    }
    
    




    // Move over X-boundary points
    for( j = 1 ; j < (ny-1) ; j++ ) {

	bmap[0][j-1] = j*nx;
	
	bmap[1][j-1] = (nx-1) + j*nx;

    }


    
}
