/*

  latticeBox3D

  lattice generation in a 3D Box

*/

#include <io.h>
#include <dictIO.h>
#include <latticeModel.h>
#include <basic.h>


void periodicXZ3D( basicMesh* mesh, uint nx, uint ny, uint nz );

void periodicYZ3D( basicMesh* mesh, uint nx, uint ny, uint nz );

void periodicXY3D( basicMesh* mesh, uint nx, uint ny, uint nz );

void genericBoundary3D( basicMesh* mesh, uint nx, uint ny, uint nz );



int main(int argc, char** argv) {

    
    printf("\n\n   LATTICE MESH GENERATION\n\n");    


    
    // Basic lattice properties

    basicMesh mesh;

    uint status;
    

    // Lattice size

    scalar dn;

    uint nx = 0,
	ny = 0,
	nz = 0;

    if(  lookUpScalarEntry("properties/latticeProperties", "Nx", -1, &dn)  )
	nx = (uint)dn;

    if(  lookUpScalarEntry("properties/latticeProperties", "Ny", -1, &dn)  )
	ny = (uint)dn;

    if(  lookUpScalarEntry("properties/latticeProperties", "Nz", -1, &dn)  )
	nz = (uint)dn;    


    mesh.nPoints = nx * ny * nz;




    
    // Lattice model

    char* modelName;
    
    latticeInfo lattice;

    lattice.model = D3Q15;
    
    status = lookUpStringEntry( "properties/latticeProperties", "LBModel", &modelName, "D3Q15" );

    if(status) {}

    if( strcmp(modelName, "D3Q15") == 0 ) {

    	lattice.model = D3Q15;

    }

    else {

	char msg[100];

	sprintf(msg, "Unrecognized model %s", modelName);
	    
	errorMsg( msg );

    }
    
    

  



    

    // ******************************************************************** //
    //                         Points inside geometry                       //
    // ******************************************************************** //

    
    printf("Adding points to lattice\n\n");

    mesh.points = matrixIntAlloc(mesh.nPoints,3,0);

        
    // Move over indices

    int i, j, k, idx;

    for( k = 0 ; k < nz ; k++) {
    
	for( j = 0 ; j < ny ; j++) {
	
	    for( i = 0 ; i < nx ; i++) {

		idx = i + j*nx + k*nx*ny;
			    
		mesh.points[idx][0] = i;
		
		mesh.points[idx][1] = j;

		mesh.points[idx][2] = k;
		
	    }
	}

    }




    
    

    // ******************************************************************** //
    //                             Neighbours                               //
    // ******************************************************************** //

    
    printf("Computing neighbour indices\n\n");

    
    // Lattice velocities
    
    int** velocities = latticeVelocities(lattice.model);

    int* rev = latticeReverseDir(lattice.model);

    
    
    // Create and resize neighbour matrix
    
    mesh.Q = latticeQ( lattice.model );

    mesh.nb = matrixIntAlloc(mesh.nPoints, mesh.Q,-1);
    

    

    // Check for neighbouring
    // There is no need to iterate over all points to look for a neighbour. Given a lattice velocity vector (x,y,z), the neighbour of a point
    // p with index pointId is at most at pointId + x + (y*Nx) + (z*Nx*Ny).

    
    // Internal points first

    int vid;

    for( k = 1 ; k < (nz-1) ; k++ ) {
    
	for( j = 1 ; j < (ny-1) ; j++ ) {
	
	    for( i = 1 ; i < (nx-1) ; i++ ) {

		idx = i + j*nx + k*nx*ny;


		// Iterate on velocities
		
		for( vid = 0 ; vid < mesh.Q ; vid++ ) {

		    mesh.nb[idx][vid] = idx   +   velocities[ rev[vid] ][0]   +   velocities[ rev[vid] ][1] * nx    +    velocities[ rev[vid] ][2] * nx * ny;

		}
	    
	    }

	}

    }

    

    // For boundary nodes, check neighbouring using distance to point

    // Y-nodes

    for( k = 0 ; k < nz ; k++ ) {

	for( j = 0 ; j < ny ; j+=(ny-1)) {
	
	    for( i = 0 ; i < nx ; i++) {

		idx = i + j*nx + k*nx*ny;

		// Iterate on velocities

		for( vid = 0 ; vid < mesh.Q ; vid++ ) {

		    int newId = idx   +   velocities[ rev[vid] ][0]   +   velocities[ rev[vid] ][1] * nx   +   velocities[ rev[vid] ][2] * nx * ny;

		    if( newId >= 0   &&   newId <= nx*ny*nz-1 ) {

			if (      (  abs( mesh.points[idx][0] - mesh.points[newId][0] ) <= 1  )
			     &&   (  abs( mesh.points[idx][1] - mesh.points[newId][1] ) <= 1  )
			     &&   (  abs( mesh.points[idx][2] - mesh.points[newId][2] ) <= 1  )  ) {
	    
			    mesh.nb[idx][vid] = newId;

			}

		    }

		}
	    
	    }

	}

    }



    // X-nodes

    for( k = 0 ; k < nz ; k++ ) {    

	for( j = 1 ; j < ny-1 ; j++ ) {
	
	    for( i = 0 ; i < nx ; i+=(nx-1)) {

		idx = i + j*nx + k*nx*ny;

		// Iterate on velocities

		for( vid = 0 ; vid < mesh.Q ; vid++ ) {

		    int newId = idx   +   velocities[ rev[vid] ][0]   +   velocities[ rev[vid] ][1] * nx   +   velocities[ rev[vid] ][2] * nx * ny;

		    if( newId >= 0   &&   newId <= nx*ny*nz-1 ) {

			if (      (  abs( mesh.points[idx][0] - mesh.points[newId][0] ) <= 1  )
			     &&   (  abs( mesh.points[idx][1] - mesh.points[newId][1] ) <= 1  )
			     &&   (  abs( mesh.points[idx][2] - mesh.points[newId][2] ) <= 1  )) {
	    
			    mesh.nb[idx][vid] = newId;

			}

		    }

		}
	    
	    }

	}

    }



    // Z-nodes

    for( k = 0 ; k < nz ; k+=(nz-1) ) {    

	for( j = 0 ; j < ny ; j++ ) {
	
	    for( i = 0 ; i < nx ; i++ ) {

		idx = i + j*nx + k*nx*ny;

		// Iterate on velocities

		for( vid = 0 ; vid < mesh.Q ; vid++ ) {

		    int newId = idx   +   velocities[ rev[vid] ][0]   +   velocities[ rev[vid] ][1] * nx   +   velocities[ rev[vid] ][2] * nx * ny;

		    if( newId >= 0   &&   newId <= nx*ny*nz-1 ) {

			if (      (  abs( mesh.points[idx][0] - mesh.points[newId][0] ) <= 1  )
			     &&   (  abs( mesh.points[idx][1] - mesh.points[newId][1] ) <= 1  )
			     &&   (  abs( mesh.points[idx][2] - mesh.points[newId][2] ) <= 1  )) {
	    
			    mesh.nb[idx][vid] = newId;

			}

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
    sprintf(mesh.bd.bdNames[4],"Z0");
    sprintf(mesh.bd.bdNames[5],"Z1");

    
    // Boundary type
    
    char* bdt;

    status = lookUpStringEntry("properties/latticeProperties","boundaryType", &bdt, "generic");

    
    // Assign points on boundary based on bdType

    // Generic
    if( strcmp(bdt,"generic") == 0) {

    	genericBoundary3D( &mesh, nx, ny, nz );

    }


    // periodicX
    else {

    	if( strcmp(bdt,"periodicX")  == 0 ) {

    	    /* periodicX( &mesh, nx, ny ); */

    	}


    	// periodicY
    	else {

    	    if( strcmp(bdt,"periodicY")  == 0 ) {

    		/* periodicY( &mesh, nx, ny ); */

    	    }


    	    // periodicXY
    	    else {

    		if( strcmp(bdt,"periodicXY")  == 0 ) {

    		    /* periodicXY( &mesh, nx, ny ); */

    		}

    		else {

    		    printf("[ERROR]   Unrecognized boundary type %s\n\n", bdt);
    		    exit(0);

    		}
	
    	    }
	
    	}

	
    }
    




	    

    


    // ******************************************************************** //
    //                             VTK Cells                                //
    // ******************************************************************** //

    printf("Creating VTK Cells\n\n");
    
    mesh.vtkCells = matrixIntAlloc((nx-1)*(ny-1)*(nz-1),8,0);

    mesh.ncells = 0;
    
    mesh.cellType = 8;

    for( k = 0 ; k < nz-1 ; k++ ) {
    
	for( j = 0 ; j < ny-1 ; j++ ) {
	
	    for( i = 0 ; i < (nx-1) ; i++ ) {

		mesh.vtkCells[mesh.ncells][0] = i   +   j*nx             +   k*nx*ny;

		mesh.vtkCells[mesh.ncells][1] = i   +   j*nx + 1         +   k*nx*ny;

		mesh.vtkCells[mesh.ncells][2] = i   +   j*nx + nx        +   k*nx*ny;

		mesh.vtkCells[mesh.ncells][3] = i   +   j*nx + nx + 1    +   k*nx*ny;

		mesh.vtkCells[mesh.ncells][4] = i   +   j*nx             +   (k+1)*nx*ny;

		mesh.vtkCells[mesh.ncells][5] = i   +   j*nx + 1         +   (k+1)*nx*ny;

		mesh.vtkCells[mesh.ncells][6] = i   +   j*nx + nx        +   (k+1)*nx*ny;

		mesh.vtkCells[mesh.ncells][7] = i   +   j*nx + nx + 1    +   (k+1)*nx*ny;
	
		mesh.ncells++;

	    }

	}

    }
    

    



    


	    


    // ******************************************************************** //
    //                             Writing                                  //
    // ******************************************************************** //
    
    printf("Writting Mesh\n\n");

    writeBasicMesh( &mesh );


    


    

    return 0;

}
