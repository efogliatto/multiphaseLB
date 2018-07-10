#include <stdio.h>
#include <stdlib.h>
#include <basicMesh.h>


void periodicXY3D( basicMesh* mesh, uint nx, uint ny, uint nz ) {


    
    // Only 2 boundaries: Z0 and Z1
    
    mesh->bd.nbd = 2;
    
    mesh->bd.nbdelem = (uint*)malloc( 2 * sizeof(uint) );
    
    mesh->bd.bdPoints = (uint**)malloc( 2 * sizeof(uint*) );


    
    

    // Number of elements per boundary
    
    mesh->bd.nbdelem[0] = nx*ny;

    mesh->bd.nbdelem[1] = nx*ny;
        
    mesh->bd.bdPoints[0] = (uint*)malloc( mesh->bd.nbdelem[0] * sizeof(uint) );
    
    mesh->bd.bdPoints[1] = (uint*)malloc( mesh->bd.nbdelem[1] * sizeof(uint) );



    

    // Boundary elements asignment

    uint i, j, k, vid, idx_0, idx_1;

    k = 0;

    for( j = 0 ; j < ny ; j++ ) {
    
	for( i = 0 ; i < nx ; i++ ) {

	    mesh->bd.bdPoints[0][k] = i + j*nx;

	    mesh->bd.bdPoints[1][k] = i + j*nx + (nz-1)*nx*ny;

	    k++;

	}

    }



    

    // Neighbour correction    


    // Move over X-boundary points

    // i = 0, i = nx-1
    // 0 < j < ny
    // 1 < k < nz - 1
    
    for( k = 1 ; k < (nz-1) ; k++ ) {
    
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
    
    for( k = 1 ; k < (nz-1) ; k++ ) {
    
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





    // Corner correction on Z = 0

    uint cid[4];

    cid[0] = 0;

    cid[1] = nx-1;

    cid[2] = nx*(ny-1);

    cid[3] = nx*ny -1;


    for( i = 0 ; i < 4 ; i++ ) {

    	for( j = 0 ; j < 4 ; j++ ) {

    	    if( i!=j )  {

    		for( vid = 1 ; vid < mesh->Q ; vid++ ) {

    		    if (  ( mesh->nb[ cid[i] ][vid] == -1)  &&  (mesh->nb[ cid[j] ][vid] != -1)  ){

    			mesh->nb[ cid[i] ][vid] = mesh->nb[cid[j] ][vid];

    		    }
		
    		}
    	    }
	    
    	}

    }

    



    // Corner correction on Z = nz - 1 

    cid[0] = 0 + (nz-1)*nx*ny;

    cid[1] = nx-1  + (nz-1)*nx*ny;

    cid[2] = nx*(ny-1)  + (nz-1)*nx*ny;

    cid[3] = nx*ny -1  + (nz-1)*nx*ny;


    for( i = 0 ; i < 4 ; i++ ) {

    	for( j = 0 ; j < 4 ; j++ ) {

    	    if( i!=j )  {

    		for( vid = 1 ; vid < mesh->Q ; vid++ ) {

    		    if (  ( mesh->nb[ cid[i] ][vid] == -1)  &&  (mesh->nb[ cid[j] ][vid] != -1)  ){

    			mesh->nb[ cid[i] ][vid] = mesh->nb[cid[j] ][vid];

    		    }
		
    		}
    	    }
	    
    	}

    }
    
    
}
