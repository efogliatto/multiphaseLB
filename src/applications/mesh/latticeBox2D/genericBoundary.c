#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;


void genericBoundary( int** neigh, unsigned int nx, unsigned int ny, unsigned int Q, int** bmap, int* btid ) {


    btid[0] = ny;
    btid[1] = ny;
    btid[2] = (nx-2);
    btid[3] = (nx-2);


    int j;


    // Move over X-boundary points
    for( j = 0 ; j < ny ; j++ ) {

	bmap[0][j] = j*nx;
	
	bmap[1][j] = (nx-1) + j*nx;

    }
    
    




    // Move over Y-boundary points
    for( j = 1 ; j < (nx-1) ; j++ ) {

	bmap[2][j-1] = j;
	
	bmap[3][j-1] = j + (nx-1)*ny;

    }


    
}
