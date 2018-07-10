#include <stdio.h>
#include <stdlib.h>
#include <basicMesh.h>


void periodicZ3D( basicMesh* mesh, uint nx, uint ny, uint nz ) {


    uint i, j, k, vid, idx_0, idx_1;
    
    
    // Only 4 boundaries: X0, X1, Y0 and Y1

    mesh->bd.nbd = 4;
    
    mesh->bd.nbdelem = (uint*)malloc( 4 * sizeof(uint) );
    
    mesh->bd.bdPoints = (uint**)malloc( 4 * sizeof(uint*) );


    
    

    // Number of elements per boundary
    
    mesh->bd.nbdelem[0] = nx*ny;

    mesh->bd.nbdelem[1] = nx*ny;

    mesh->bd.nbdelem[2] = (nx-2)*ny;

    mesh->bd.nbdelem[3] = (nx-2)*ny;

    for( i = 0 ; i < mesh->bd.nbd ; i++ ) {
    
	mesh->bd.bdPoints[i] = (uint*)malloc( mesh->bd.nbdelem[i] * sizeof(uint) );

    }
   




    // Boundary elements asignment

    // X-boundary

    i = 0;

    for( k = 0 ; k < nz ; k++ ) {
    
	for( j = 0 ; j < ny ; j++ ) {

	    mesh->bd.bdPoints[0][i] = j*nx + k*nx*ny;

	    mesh->bd.bdPoints[1][i] = (nx-1) + j*nx + k*nx*ny;

	    i++;

	}

    }



    // Y-boundary

    j = 0;

    for( k = 0 ; k < nz ; k++ ) {
    
	for( i = 1 ; i < (nx-1) ; i++ ) {

	    mesh->bd.bdPoints[2][j] = i + k*nx*ny;

	    mesh->bd.bdPoints[3][j] = i  +  (ny-1)*nx  +  k*nx*ny;

	    j++;

	}

    }    

    



    // Neighbour correction    


    // Move over Z-boundary points

    // 1 < i < nx - 1
    // 1 < j < ny - 1
    // k = 0, k = nz - 1
    
    
    for( j = 1 ; j < (ny-1) ; j++ ) {
    
    	for( i = 1 ; i < (nx-1) ; i++ ) {

	    
	    idx_0 = i + j*nx;

	    idx_1 = idx_0 + (nz-1)*nx*ny;



    	    for( vid = 0 ; vid < mesh->Q ; vid++ ) {
		
		
    		// Z = 0
		
    		if(mesh->nb[idx_0][vid] == -1) {

    		    mesh->nb[idx_0][vid] = mesh->nb[idx_1][vid];

    		}


    		// Z = nz - 1

    		if(mesh->nb[idx_1][vid] == -1) {

    		    mesh->nb[idx_1][vid] = mesh->nb[idx_0][vid];

    		}
	    
    	    }

    	}

    }
    




    // Correct periodicity on y edges in z-direction

    for( i = 0 ; i < nx ; i++ ) {

	idx_0 = i;

	idx_1 = idx_0 + (nz-1)*nx*ny;

	for( vid = 0 ; vid < mesh->Q ; vid++ ) {
		
	    if(mesh->nb[idx_0][vid] == -1) {

		mesh->nb[idx_0][vid] = mesh->nb[idx_1][vid];

	    }

	    if(mesh->nb[idx_1][vid] == -1) {

		mesh->nb[idx_1][vid] = mesh->nb[idx_0][vid];

	    }
	    
	}



	idx_0 = i + (ny-1)*nx;

	idx_1 = idx_0 + (nz-1)*nx*ny;

	for( vid = 0 ; vid < mesh->Q ; vid++ ) {
		
	    if(mesh->nb[idx_0][vid] == -1) {

		mesh->nb[idx_0][vid] = mesh->nb[idx_1][vid];

	    }

	    if(mesh->nb[idx_1][vid] == -1) {

		mesh->nb[idx_1][vid] = mesh->nb[idx_0][vid];

	    }
	    
	}
	

    }










    // Correct periodicity on x edges in z-direction

    for( j = 1 ; j < (ny-1) ; j++ ) {

	idx_0 = j*ny;

	idx_1 = idx_0 + (nz-1)*nx*ny;

	for( vid = 0 ; vid < mesh->Q ; vid++ ) {
		
	    if(mesh->nb[idx_0][vid] == -1) {

		mesh->nb[idx_0][vid] = mesh->nb[idx_1][vid];

	    }

	    if(mesh->nb[idx_1][vid] == -1) {

		mesh->nb[idx_1][vid] = mesh->nb[idx_0][vid];

	    }
	    
	}



	idx_0 = (nx-1) + j*nx;

	idx_1 = idx_0 + (nz-1)*nx*ny;

	for( vid = 0 ; vid < mesh->Q ; vid++ ) {
		
	    if(mesh->nb[idx_0][vid] == -1) {

		mesh->nb[idx_0][vid] = mesh->nb[idx_1][vid];

	    }

	    if(mesh->nb[idx_1][vid] == -1) {

		mesh->nb[idx_1][vid] = mesh->nb[idx_0][vid];

	    }
	    
	}
	

    }
    
    
    


    
}
