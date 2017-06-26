/*

  latticeBox2D

  lattice generation in a 2D Box

*/

#include <io.h>
#include <latticeModel.h>
#include <basic.h>

typedef unsigned int uint;


void periodicX( struct basicMesh* mesh, unsigned int nx, unsigned int ny );
void periodicY( struct basicMesh* mesh, unsigned int nx, unsigned int ny );
void periodicXY( struct basicMesh* mesh, unsigned int nx, unsigned int ny );
void genericBoundary( struct basicMesh* mesh, unsigned int nx, unsigned int ny );

int main(int argc, char** argv) {

    
    printf("\n\n   LATTICE MESH GENERATION\n\n");

    struct basicMesh mesh;


    
    // Basic lattice properties
    

    // Lattice size
    uint nx = (uint)lookUpDoubleEntry("properties/latticeProperties","Nx",-1);
    uint ny = (uint)lookUpDoubleEntry("properties/latticeProperties","Ny",-1);
    mesh.nPoints = nx*ny;

    // Lattice model
    lookUpStringEntry("properties/latticeProperties","LBModel",mesh.lbm);

    // Boundary type
    char bdType[100];
    lookUpStringEntry("properties/latticeProperties","boundaryType",bdType);
    



    

    // ******************************************************************** //
    //                         Points inside geometry                       //
    // ******************************************************************** //

    
    printf("Adding points to lattice\n\n");

    mesh.points = matrixIntAlloc(mesh.nPoints,3,0);

        
    // Move over indices

    int i,j;

    for( j = 0 ; j < ny ; j++) {
	
    	for( i = 0 ; i < nx ; i++) {
			    
    	    mesh.points[i+j*nx][0] = i;
	    mesh.points[i+j*nx][1] = j;
		
    	}
    }




    
    

    // ******************************************************************** //
    //                             Neighbours                               //
    // ******************************************************************** //

    
    printf("Computing neighbour indices\n\n");

    
    // Lattice velocities
    int** velocities = latticeVelocities(mesh.lbm);
    int* rev = latticeReverseDir(mesh.lbm);
    
    // Create and resize neighbour matrix
    mesh.Q = latticeQ( mesh.lbm );
    mesh.nb = matrixIntAlloc(mesh.nPoints, mesh.Q,-1);
    

    

    // Check for neighbouring
    // There is no need to iterate over all points to look for a neighbour. Given a lattice velocity vector (x,y,z), the neighbour of a point
    // p with index pointId is at most at pointId + x + (y*Nx).

    
    // Internal points first

    int pointId, velId;
    
    for( j = 1 ; j < (ny-1) ; j++) {
	
    	for( i = 1 ; i < (nx-1) ; i++) {

    	    pointId = i+j*nx;


    	    // Iterate on velocities
    	    for( velId = 0 ; velId < mesh.Q ; velId++ ) {

    		mesh.nb[pointId][velId] = pointId   +   velocities[ rev[velId] ][0]   +   velocities[ rev[velId] ][1] * nx;

    	    }
	    
    	}

    }

    

    // For boundary nodes, check neighbouring using distance to point

    for( j = 0 ; j < ny ; j+=(ny-1)) {
	
    	for( i = 0 ; i < nx ; i++) {

    	    pointId = i+j*nx;

    	    // Iterate on velocities
    	    for( velId = 0 ; velId < mesh.Q ; velId++ ) {

    		int newId = pointId   +   velocities[ rev[velId] ][0]   +   velocities[ rev[velId] ][1] * nx;

    		if( newId >= 0   &&   newId <= nx*ny-1 ) {

    		    if ( (  abs( mesh.points[pointId][0] - mesh.points[newId][0] ) <= 1  )   &&   (  abs( mesh.points[pointId][1] - mesh.points[newId][1] ) <= 1  )  ) {
	    
    			mesh.nb[pointId][velId] = newId;

    		    }

    		}

    	    }
	    
    	}

    }


    for( j = 1 ; j < ny-1 ; j++ ) {
	
    	for( i = 0 ; i < nx ; i+=(nx-1)) {

    	    pointId = i+j*nx;

    	    // Iterate on velocities
    	    for( velId = 0 ; velId < mesh.Q ; velId++ ) {

    		int newId = pointId   +   velocities[ rev[velId] ][0]   +   velocities[ rev[velId] ][1] * nx;

    		if( newId >= 0   &&   newId <= nx*ny-1 ) {

    		    if ( (  abs( mesh.points[pointId][0] - mesh.points[newId][0] ) <= 1  )   &&   (  abs( mesh.points[pointId][1] - mesh.points[newId][1] ) <= 1  )  ) {
	    
    			mesh.nb[pointId][velId] = newId;

    		    }

    		}

    	    }
	    
    	}

    }
    


    	




    

	    
    
    // ******************************************************************** //
    //                             Boundary                                 //
    // ******************************************************************** //

    printf("Computing boundary nodes\n\n");

    sprintf(mesh.bd.bdNames[0],"X0");
    sprintf(mesh.bd.bdNames[1],"X1");
    sprintf(mesh.bd.bdNames[2],"Y0");
    sprintf(mesh.bd.bdNames[3],"Y1");

    

    // Assign points on boundary based on bdType

    // Generic
    if( strcmp(bdType,"generic") == 0) {

    	genericBoundary( &mesh, nx, ny );

    }


    // periodicX
    else {

    	if( strcmp(bdType,"periodicX")  == 0 ) {

    	    periodicX( &mesh, nx, ny );

    	}


    	// periodicY
    	else {

    	    if( strcmp(bdType,"periodicY")  == 0 ) {

    		periodicY( &mesh, nx, ny );

    	    }


    	    // periodicXY
    	    else {

    		if( strcmp(bdType,"periodicXY")  == 0 ) {

    		    periodicXY( &mesh, nx, ny );

    		}

    		else {

    		    printf("[ERROR]   Unrecognized boundary type %s\n\n", bdType);
    		    exit(0);

    		}
	
    	    }
	
    	}

	
    }
    




	    

    


    // ******************************************************************** //
    //                             VTK Cells                                //
    // ******************************************************************** //

    printf("Creating VTK Cells\n\n");
    
    mesh.vtkCells = matrixIntAlloc((nx-1)*(ny-1),4,0);

    mesh.ncells = 0;
    mesh.cellType = 4;
    
    for( j = 0 ; j < ny-1 ; j++ ) {
	
    	for( i = 0 ; i < (nx-1) ; i++ ) {

    	    mesh.vtkCells[mesh.ncells][0] = i + j*nx;
    	    mesh.vtkCells[mesh.ncells][1] = i + j*nx + 1;
    	    mesh.vtkCells[mesh.ncells][2] = i + j*nx + nx;
    	    mesh.vtkCells[mesh.ncells][3] = i + j*nx + nx + 1;
	
    	    mesh.ncells++;

    	}

    }
    

    



    


	    


    // ******************************************************************** //
    //                             Writing                                  //
    // ******************************************************************** //
    
    printf("Writting Mesh\n\n");

    writeBasicMesh( &mesh );


    


    

    return 0;

}
