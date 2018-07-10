#include <stdio.h>
#include <stdlib.h>
#include <basicMesh.h>


void periodicXYZ3D( basicMesh* mesh, uint nx, uint ny, uint nz ) {


    
    // No boundaries
    
    mesh->bd.nbd = 0;


    

    // Neighbour correction    

    uint i, j, k, vid, idx_0, idx_1;

    
    

    // Move over X-boundary points

    // i = 0, i = nx-1
    // 0 < j < ny
    // 1 < k < nz - 1
    
    for( k = 0 ; k < nz ; k++ ) {
    
    	for( j = 0 ; j < ny ; j++ ) {

	    
	    idx_0 = j*nx + k*nx*ny;

	    idx_1 = idx_0 + nx - 1;


    	    for( vid = 0 ; vid < mesh->Q ; vid++ ) {
		
		
    		// X = 0
		
    		if(mesh->nb[idx_0][vid] == -1) {

    		    mesh->nb[idx_0][vid] = mesh->nb[idx_1][vid];

    		}


    		// X = nx

    		if(mesh->nb[idx_1][vid] == -1) {

    		    mesh->nb[idx_1][vid] = mesh->nb[idx_0][vid];

    		}
	    
    	    }

    	}

    }




    // Move over Y-boundary points

    // 0 < i < nx
    // j = 0, j = ny -1
    // 1 < k < nz - 1
    
    for( k = 0 ; k < nz ; k++ ) {
    
    	for( i = 0 ; i < nx ; i++ ) {

	    
	    idx_0 = i  +  k*nx*ny;

	    idx_1 = idx_0 + (ny-1)*nx;

	    
    	    for( vid = 0 ; vid < mesh->Q ; vid++ ) {

		
		
    		// Y = 0
		
    		if(mesh->nb[idx_0][vid] == -1) {

    		    mesh->nb[idx_0][vid] = mesh->nb[idx_1][vid];

    		}


    		// Y = ny

    		if(mesh->nb[idx_1][vid] == -1) {

    		    mesh->nb[idx_1][vid] = mesh->nb[idx_0][vid];

    		}
	    
    	    }

    	}

    }




    // Move over Z-boundary points

    // 0 < i < nx
    // j = 0, j = ny -1
    // 1 < k < nz - 1
    
    for( j = 0 ; j < ny ; j++ ) {
    
    	for( i = 0 ; i < nx ; i++ ) {

	    
	    idx_0 = i  +  j*nx;

	    idx_1 = idx_0 + (nz-1)*nx*ny;

	    
    	    for( vid = 0 ; vid < mesh->Q ; vid++ ) {

		
		
    		// Y = 0
		
    		if(mesh->nb[idx_0][vid] == -1) {

    		    mesh->nb[idx_0][vid] = mesh->nb[idx_1][vid];

    		}


    		// Y = ny

    		if(mesh->nb[idx_1][vid] == -1) {

    		    mesh->nb[idx_1][vid] = mesh->nb[idx_0][vid];

    		}
	    
    	    }

    	}

    }
    
    
}
