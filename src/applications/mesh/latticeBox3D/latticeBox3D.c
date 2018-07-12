/*

  latticeBox3D

  lattice generation in a 3D Box

*/

#include <io.h>
#include <dictIO.h>
#include <latticeModel.h>
#include <basic.h>


void periodicXY3D( basicMesh* mesh, uint nx, uint ny, uint nz );

void periodicXYZ3D( basicMesh* mesh, uint nx, uint ny, uint nz );

void periodicZ3D( basicMesh* mesh, uint nx, uint ny, uint nz );

void genericBoundary3D( basicMesh* mesh, uint nx, uint ny, uint nz );



int main(int argc, char** argv) {

    
    printf("\n\n   LATTICE MESH GENERATION\n\n");    


    
    // Basic lattice properties

    basicMesh mesh;

    uint status;
    

    // Lattice size

    int dn;

    uint nx = 0,
	ny = 0,
	nz = 0;

    if(  lookUpIntegerEntry("properties/latticeProperties", "Nx", -1, &dn)  )
	nx = (uint)dn;

    if(  lookUpIntegerEntry("properties/latticeProperties", "Ny", -1, &dn)  )
	ny = (uint)dn;

    if(  lookUpIntegerEntry("properties/latticeProperties", "Nz", -1, &dn)  )
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

    mesh.nb = matrixIntAlloc(mesh.nPoints, mesh.Q, -1);
    

    

    // Check for neighbouring
    // There is no need to iterate over all points to look for a neighbour. Given a lattice velocity vector (x,y,z), the neighbour of a point
    // p with index pointId is at most at pointId + x + (y*Nx) + (z*Nx*Ny).
    // For boundary nodes, check neighbouring using distance to point
    

    int vid, newId;

    for( k = 0 ; k < nz ; k++ ) {

    	for( j = 0 ; j < ny ; j++) {
	
    	    for( i = 0 ; i < nx ; i++) {


		idx = i + j*nx + k*nx*ny;
		
		
		// Boundary nodes
		
    		if( (i == 0)  ||  (i == nx-1)   ||   (j == 0)  ||  (j == ny-1)   ||   (k == 0)  ||  (k == nz-1) ) {	       		    

    		    for( vid = 0 ; vid < mesh.Q ; vid++ ) {

    			newId = idx   +   velocities[ rev[vid] ][0]   +   velocities[ rev[vid] ][1] * nx   +   velocities[ rev[vid] ][2] * nx * ny;

    			if( newId >= 0   &&   newId <= nx*ny*nz-1 ) {

    			    if (      (  abs( mesh.points[idx][0] - mesh.points[newId][0] ) <= 1  )
    				      &&   (  abs( mesh.points[idx][1] - mesh.points[newId][1] ) <= 1  )
    				      &&   (  abs( mesh.points[idx][2] - mesh.points[newId][2] ) <= 1  )  ) {
	    
    				mesh.nb[idx][vid] = newId;

    			    }

    			}

    		    }

    		}


		
		// Inner nodes
		
		else {

		    for( vid = 0 ; vid < mesh.Q ; vid++ ) {

			mesh.nb[idx][vid] = idx   +   velocities[ rev[vid] ][0]   +   velocities[ rev[vid] ][1] * nx    +    velocities[ rev[vid] ][2] * nx * ny;

		    }

		}

		
	    
    	    }

    	}

    }
    
    

       


    

	    
    
    // ******************************************************************** //
    //                             Boundary                                 //
    // ******************************************************************** //

    printf("Computing boundary nodes\n\n");

    
    // Boundary type
    
    char* bdt;

    status = lookUpStringEntry("properties/latticeProperties","boundaryType", &bdt, "generic");

    
    // Assign points on boundary based on bdType

    // Generic
    if( strcmp(bdt,"generic") == 0) {

    	genericBoundary3D( &mesh, nx, ny, nz );

	sprintf(mesh.bd.bdNames[0],"X0");
	
	sprintf(mesh.bd.bdNames[1],"X1");

	sprintf(mesh.bd.bdNames[2],"Y0");

	sprintf(mesh.bd.bdNames[3],"Y1");

	sprintf(mesh.bd.bdNames[4],"Z0");

	sprintf(mesh.bd.bdNames[5],"Z1");

    }


    // periodicXY
    else {

    	if( strcmp(bdt,"periodicXY")  == 0 ) {

    	    periodicXY3D( &mesh, nx, ny, nz );

	    sprintf(mesh.bd.bdNames[0],"Z0");
	
	    sprintf(mesh.bd.bdNames[1],"Z1");  

    	}


    	// periodicZ
    	else {

    	    if( strcmp(bdt,"periodicZ")  == 0 ) {

    		periodicZ3D( &mesh, nx, ny, nz );

		sprintf(mesh.bd.bdNames[0],"X0");
	
		sprintf(mesh.bd.bdNames[1],"X1");

		sprintf(mesh.bd.bdNames[2],"Y0");

		sprintf(mesh.bd.bdNames[3],"Y1");	

    	    }


	    // Fully periodic
	    
	    else {

		if( strcmp(bdt,"periodicXYZ")  == 0 ) {

		    periodicXYZ3D( &mesh, nx, ny, nz );
		    
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
