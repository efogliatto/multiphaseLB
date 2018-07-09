#include <stdio.h>
#include <stdlib.h>
#include <basicMesh.h>


void genericBoundary3D( basicMesh* mesh, uint nx, uint ny, uint nz ) {

    mesh->bd.nbd = 6;
    
    mesh->bd.nbdelem = (uint*)malloc( 6 * sizeof(uint) );
    mesh->bd.bdPoints = (uint**)malloc( 6 * sizeof(uint*) );

    mesh->bd.nbdelem[0] = ny*nz;
    mesh->bd.nbdelem[1] = ny*nz;
    mesh->bd.nbdelem[2] = (nx-2)*nz;
    mesh->bd.nbdelem[3] = (nx-2)*nz;
    mesh->bd.nbdelem[4] = (nx-2)*(ny-2);
    mesh->bd.nbdelem[5] = (nx-2)*(ny-2);

    
    mesh->bd.bdPoints[0] = (uint*)malloc( mesh->bd.nbdelem[0] * sizeof(uint) );
    mesh->bd.bdPoints[1] = (uint*)malloc( mesh->bd.nbdelem[1] * sizeof(uint) );
    mesh->bd.bdPoints[2] = (uint*)malloc( mesh->bd.nbdelem[2] * sizeof(uint) );
    mesh->bd.bdPoints[3] = (uint*)malloc( mesh->bd.nbdelem[3] * sizeof(uint) );   
    mesh->bd.bdPoints[4] = (uint*)malloc( mesh->bd.nbdelem[4] * sizeof(uint) );
    mesh->bd.bdPoints[5] = (uint*)malloc( mesh->bd.nbdelem[5] * sizeof(uint) );   


    
    int i, j, k, id;


    // Move over X-boundary points

    id = 0;
    
    for( k = 0 ; k < nz ; k++ ) {

	for( j = 0 ; j < ny ; j++ ) {

	    mesh->bd.bdPoints[0][id] = j*nx + k*nx*ny;
	
	    mesh->bd.bdPoints[1][id] = (nx-1) + j*nx + k*nx*ny;

	    id++;

	}
	
    }
    


    
    // Move over Y-boundary points

    id = 0;
    
    for( k = 0 ; k < nz ; k++ ) {
    
	for( i = 1 ; i < (nx-1) ; i++ ) {

	    mesh->bd.bdPoints[2][id] = i + k*nx*ny; 
	
	    mesh->bd.bdPoints[3][id] = i + (ny-1)*nx + k*nx*ny;

	    id++;

	}

    }

    

    // Move over Z-boundary points

    id = 0;
    
    for( j = 1 ; j < (ny-1) ; j++ ) {
    
    	for( i = 1 ; i < (nx-1) ; i++ ) {

    	    mesh->bd.bdPoints[4][id] = i + j*nx;
	
    	    mesh->bd.bdPoints[5][id] = i + j*nx + (nz-1)*nx*ny;

	    id++;
	    
    	}

    }
    
    
}
