#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;


void periodicXY( int** neigh, unsigned int nx, unsigned int ny, unsigned int Q, int** bmap, int* btid ) {


    btid[0] = 0;
    btid[1] = 0;
    btid[2] = 0;
    btid[3] = 0;


    int i,
	j,
	velId;


    // Move over X-boundary points
    for( j = 1 ; j < (ny-1) ; j++ ) {

    	// Assign periodic neighbours
    	for( velId = 0 ; velId < Q ; velId++ ) {

    	    if(neigh[j*nx][velId] == -1) {

    		neigh[j*nx][velId] = neigh[ nx-1+j*nx  ][velId];

    	    }

    	    if(neigh[nx-1+j*nx][velId] == -1) {

    		neigh[nx-1+j*nx][velId] = neigh[j*nx][velId];

    	    }
	    
    	}	

    }
    



    // Move over Y-boundary points
    for( j = 1 ; j < (nx-1) ; j++ ) {

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




    // Resolve for corners
    int cid[4];
    cid[0] = 0;
    cid[1] = nx-1;
    cid[2] = nx*(ny-1);
    cid[3] = nx*ny -1;

    for( i = 0 ; i < 4 ; i++ ) {

	for( j = 0 ; j < 4 ; j++ ) {

	    if( i!=j )  {

		for( velId = 1 ; velId < Q ; velId++ ) {

		    if (  ( neigh[ cid[i] ][velId] == -1)  &&  (neigh[ cid[j] ][velId] != -1)  ){

			neigh[ cid[i] ][velId] = neigh[cid[j] ][velId];

		    }
		
		}
	    }
	    
	}

    }

    

    
}
