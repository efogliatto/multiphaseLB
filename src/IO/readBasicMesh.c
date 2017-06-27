#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <basicMesh.h>
#include <basic.h>
#include <io.h>
#include <latticeModel.h>

struct basicMesh readBasicMesh() {

    struct basicMesh mesh;

    uint i,j;

    int status;

    

    // ******************************************************************** //
    //                         Points inside geometry                       //
    // ******************************************************************** //

    printf("Reading Mesh points\n\n");

    // Open file
    FILE* inFile = fopen( "lattice/points", "r" );
    
    // Number of points
    status = fscanf(inFile, "%d", &mesh.nPoints);

    // Read Mesh points
    mesh.points = matrixIntAlloc(mesh.nPoints,3,0);
    for( i = 0 ; i < mesh.nPoints ; i++ ) {

	status = fscanf(inFile, "%d", &mesh.points[i][0]);
	status = fscanf(inFile, "%d", &mesh.points[i][1]);
	status = fscanf(inFile, "%d", &mesh.points[i][2]);

    }

    fclose(inFile);





    

    // ******************************************************************** //
    //                             Neighbours                               //
    // ******************************************************************** //

    printf("Reading Neighbour indices\n\n");

    // Open file
    inFile = fopen( "lattice/neighbours", "r" );

    // Lattice Model   
    lookUpStringEntry("properties/latticeProperties","LBModel",mesh.lbm);
    mesh.Q = latticeQ(mesh.lbm);

    // Read neighbours
    mesh.nb = matrixIntAlloc(mesh.nPoints, mesh.Q, -1);
    for( i = 0 ; i < mesh.nPoints ; i++ ) {

	for( j = 0 ; j < mesh.Q ; j++ ) {

	    status = fscanf(inFile, "%d", &mesh.nb[i][j]);

	}

    }

    fclose(inFile);




    

    // ******************************************************************** //
    //                             VTK Cells                                //
    // ******************************************************************** //

    printf("Reading vtkCells\n\n");

    // Open file
    inFile = fopen( "lattice/vtkCells", "r" );

    // Number of cells and points per cell
    status = fscanf(inFile, "%d", &mesh.ncells);
    status = fscanf(inFile, "%d", &mesh.cellType);
    
    // Read cells
    mesh.vtkCells = matrixIntAlloc(mesh.ncells, mesh.cellType, -1);
    
    for( i = 0 ; i < mesh.ncells ; i++ ) {

	for( j = 0 ; j < mesh.cellType ; j++ ) {

	    status = fscanf(inFile, "%d", &mesh.vtkCells[i][j]);

	}

    }

    fclose(inFile);








    // ******************************************************************** //
    //                        Reading boundary nodes                        //
    // ******************************************************************** //

    printf("Reading boundary nodes\n\n");

    // Open boundary file
    inFile = fopen( "lattice/boundary", "r" );
    
    // Number of boundary types
    status = fscanf(inFile, "%d\n", &mesh.bd.nbd);

    // Total number of elements per boundary type
    mesh.bd.nbdelem = (uint*)malloc(mesh.bd.nbd * sizeof(uint));

    // Elements in boundary
    mesh.bd.bdPoints = (uint**)malloc( mesh.bd.nbd * sizeof(uint*) );
    

    // Read boundary
    for( i = 0 ; i < mesh.bd.nbd ; i++ ) {

    	// Boundary name
	status = fscanf(inFile, "%s", mesh.bd.bdNames[i]);

    	// Elements in boundary
    	status = fscanf(inFile, "%d", &mesh.bd.nbdelem[i]);

    	// Resize bdPoints
    	mesh.bd.bdPoints[i] = (uint*)malloc( mesh.bd.nbdelem[i] * sizeof(uint) );
	
    	for( j = 0 ; j < mesh.bd.nbdelem[i] ; j++ ) {

    	    status = fscanf(inFile, "%d", &mesh.bd.bdPoints[i][j]);

    	}

    }
    



    if (status) {}
    
    return mesh;
    
}
