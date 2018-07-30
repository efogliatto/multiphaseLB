#include <stdio.h>
#include <stdlib.h>
#include <basicMesh.h>
#include <dictIO.h>


void periodicXY3DSpot( basicMesh* mesh, uint nx, uint ny, uint nz ) {


    
    // Only 3 boundaries: Z0, Z1 and spot
    
    mesh->bd.nbd = 3;
    
    mesh->bd.nbdelem = (uint*)malloc( 3 * sizeof(uint) );
    
    mesh->bd.bdPoints = (uint**)malloc( 3 * sizeof(uint*) );




    // Read radius

    scalar radius;

    uint status;
    
    status = lookUpScalarEntry("properties/latticeProperties", "spot/radius", 0, &radius);

    if (status) {}
    


    // Read centre

    scalar* centre;

    uint n;
    
    status = lookUpVectorEntry("properties/latticeProperties", "spot/centre", &centre, &n);



    
    // Count number of nodes inside spot

    uint i, j, count = 0;

    int x0, y0;

    for( i = 0 ; i < nx ; i++ ) {

    	for( j = 0 ; j < ny ; j++ ) {

    	    x0 = centre[0] - (int)i;

    	    y0 = centre[1] - (int)j;
	    
    	    if( (x0*x0 + y0*y0) <= radius*radius ) {

    		count++;

    	    }

    	}

    }

	

    
    

    // Number of elements per boundary
    
    mesh->bd.nbdelem[0] = nx*ny - count;

    mesh->bd.nbdelem[1] = nx*ny;

    mesh->bd.nbdelem[2] = count;    
        
    mesh->bd.bdPoints[0] = (uint*)malloc( mesh->bd.nbdelem[0] * sizeof(uint) );
    
    mesh->bd.bdPoints[1] = (uint*)malloc( mesh->bd.nbdelem[1] * sizeof(uint) );

    mesh->bd.bdPoints[2] = (uint*)malloc( mesh->bd.nbdelem[2] * sizeof(uint) );



    

    // Boundary elements asignment

    uint k, vid, idx_0, idx_1;

    k = 0;

    uint k0 = 0, ks = 0;

    for( j = 0 ; j < ny ; j++ ) {
    
    	for( i = 0 ; i < nx ; i++ ) {

	    // Z1
	    
    	    mesh->bd.bdPoints[1][k] = i + j*nx + (nz-1)*nx*ny;


	    

	    x0 = centre[0] - (int)i;

    	    y0 = centre[1] - (int)j;


	    // Spot
	    
    	    if( (x0*x0 + y0*y0) <= radius*radius ) {

		mesh->bd.bdPoints[2][ks] = i + j*nx;

		ks++;

    	    }

	    

	    // Z0
	    else {

		mesh->bd.bdPoints[0][k0] = i + j*nx;

		k0++;

	    }

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
