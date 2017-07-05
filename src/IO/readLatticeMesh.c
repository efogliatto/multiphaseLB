#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <latticeMesh.h>
#include <basic.h>
#include <io.h>
#include <latticeModel.h>

struct latticeMesh readLatticeMesh( unsigned int pid ) {

    
    
    struct latticeMesh mesh;

    uint i,j,status;

    char command[100];

    FILE* inFile;

    

    
    // Basic information

    mesh.parallel.pid = pid;


    // Time information
    readTimeInfo( &mesh );

    

    

    // ******************************************************************** //
    //                         Points inside geometry                       //
    // ******************************************************************** //



    // Local points
    
    sprintf(command,"processor%d/lattice/points", pid);

    inFile = fopen( command, "r" );

    status = fscanf(inFile, "%d", &mesh.parallel.nlocal);
    
    fclose(inFile);



    // Ghost points
    
    sprintf(command,"processor%d/lattice/ghosts", pid);

    inFile = fopen( command, "r" );

    status = fscanf(inFile, "%d", &mesh.parallel.nghosts);
    
    fclose(inFile);


    
    // Resize arrays
    
    mesh.mesh.nPoints = mesh.parallel.nlocal + mesh.parallel.nghosts;

    mesh.mesh.points = matrixIntAlloc( mesh.mesh.nPoints, 3, 0 );

    

    // Read all points

    sprintf(command,"processor%d/lattice/points", pid);

    inFile = fopen( command, "r" );

    status = fscanf(inFile, "%d", &mesh.parallel.nlocal);

    for( i = 0 ; i < mesh.parallel.nlocal ; i++ ) {

	status = fscanf(inFile, "%d", &mesh.mesh.points[i][0]);

	status = fscanf(inFile, "%d", &mesh.mesh.points[i][1]);

	status = fscanf(inFile, "%d", &mesh.mesh.points[i][2]);

    }

    fclose(inFile);


    sprintf(command,"processor%d/lattice/ghosts", pid);

    inFile = fopen( command, "r" );

    status = fscanf(inFile, "%d", &mesh.parallel.nghosts);

    for( i = mesh.parallel.nlocal ; i < mesh.mesh.nPoints ; i++ ) {

	status = fscanf(inFile, "%d", &mesh.mesh.points[i][0]);

	status = fscanf(inFile, "%d", &mesh.mesh.points[i][1]);

	status = fscanf(inFile, "%d", &mesh.mesh.points[i][2]);

    }

    fclose(inFile);


    





    

    // ******************************************************************** //
    //                             Neighbours                               //
    // ******************************************************************** //


    lookUpStringEntry("properties/latticeProperties", "LBModel", mesh.mesh.lbm);

    mesh.mesh.Q = latticeQ( mesh.mesh.lbm );

    mesh.lattice.Q = mesh.mesh.Q;

    mesh.mesh.nb = matrixIntAlloc( mesh.parallel.nlocal, mesh.mesh.Q, -1 );

    
    sprintf(command,"processor%d/lattice/neighbours", pid);

    inFile = fopen( command, "r" );

    for( i = 0 ; i < mesh.parallel.nlocal ; i++ ) {

	for( j = 0 ; j < mesh.mesh.Q ; j++ ) {

	    status = fscanf(inFile, "%d", &mesh.mesh.nb[i][j]);

	}

    }

    fclose(inFile);





    
    

    // ******************************************************************** //
    //                             VTK Cells                                //
    // ******************************************************************** //


    sprintf(command,"processor%d/lattice/vtkCells", pid);

    inFile = fopen( command, "r" );


    // Number of cells and points per cell
    status = fscanf(inFile, "%d", &mesh.mesh.ncells);

    status = fscanf(inFile, "%d", &mesh.mesh.cellType);

    
    mesh.mesh.vtkCells = matrixIntAlloc(mesh.mesh.ncells, mesh.mesh.cellType, -1);
    
    for( i = 0 ; i < mesh.mesh.ncells ; i++ ) {

    	for( j = 0 ; j < mesh.mesh.cellType ; j++ ) {

    	    status = fscanf(inFile, "%d", &mesh.mesh.vtkCells[i][j]);

    	}

    }

    fclose(inFile);








    // ******************************************************************** //
    //                        Reading boundary nodes                        //
    // ******************************************************************** //

    
    sprintf(command,"processor%d/lattice/boundary", pid);

    inFile = fopen( command, "r" );

    
    // Number of boundary types
    status = fscanf(inFile, "%d\n", &mesh.mesh.bd.nbd);

    // Total number of elements per boundary type
    mesh.mesh.bd.nbdelem = (uint*)malloc(mesh.mesh.bd.nbd * sizeof(uint));

    // Elements in boundary
    mesh.mesh.bd.bdPoints = (uint**)malloc( mesh.mesh.bd.nbd * sizeof(uint*) );
    

    // Read boundary
    for( i = 0 ; i < mesh.mesh.bd.nbd ; i++ ) {

    	// Boundary name
    	status = fscanf(inFile, "%s", mesh.mesh.bd.bdNames[i]);

    	// Elements in boundary
    	status = fscanf(inFile, "%d", &mesh.mesh.bd.nbdelem[i]);

    	// Resize bdPoints
    	mesh.mesh.bd.bdPoints[i] = (uint*)malloc( mesh.mesh.bd.nbdelem[i] * sizeof(uint) );
	
    	for( j = 0 ; j < mesh.mesh.bd.nbdelem[i] ; j++ ) {

    	    status = fscanf(inFile, "%d", &mesh.mesh.bd.bdPoints[i][j]);

    	}

    }

    
    fclose(inFile);







    // ******************************************************************** //
    //                                Recv Ghosts                           //
    // ******************************************************************** //

    
    sprintf(command,"processor%d/lattice/recvGhosts", pid);

    inFile = fopen( command, "r" );

  
    status = fscanf(inFile, "%d\n", &mesh.parallel.worldSize);

    mesh.parallel.shared     = (uint*)malloc( mesh.parallel.worldSize * sizeof(uint) );

    mesh.parallel.recvGhosts = (uint**)malloc( mesh.parallel.worldSize * sizeof(uint*) );
    
   
    
    for( i = 0 ; i < mesh.parallel.worldSize ; i++ ) {

	
    	status = fscanf(inFile, "%d", &mesh.parallel.shared[i] );

	status = fscanf(inFile, "%d", &mesh.parallel.shared[i] );
	

	mesh.parallel.recvGhosts[i] = (uint*)malloc( mesh.parallel.shared[i] * sizeof(uint) );

	
    	for( j = 0 ; j < mesh.parallel.shared[i] ; j++ ) {

    	    status = fscanf( inFile, "%d", &mesh.parallel.recvGhosts[i][j] );

    	}

    }

    
    fclose(inFile);



    // Resize mpi recv buffer

    mesh.parallel.rbuf = (double**)malloc( mesh.parallel.worldSize * sizeof(double*) );

    mesh.parallel.vrbuf = (double**)malloc( mesh.parallel.worldSize * sizeof(double*) );
    
    for( i = 0 ; i < mesh.parallel.worldSize ; i++ ) {

	mesh.parallel.rbuf[i] = (double*)malloc( mesh.parallel.shared[i] * mesh.mesh.Q * sizeof(double) );

	mesh.parallel.vrbuf[i] = (double*)malloc( mesh.parallel.shared[i] * 3 * sizeof(double) );

    }








    // ******************************************************************** //
    //                                Send Ghosts                           //
    // ******************************************************************** //

    
    sprintf(command,"processor%d/lattice/sendGhosts", pid);

    inFile = fopen( command, "r" );

  
    status = fscanf(inFile, "%d\n", &mesh.parallel.worldSize);

    mesh.parallel.sendGhosts = (uint**)malloc( mesh.parallel.worldSize * sizeof(uint*) );
    
   
    
    for( i = 0 ; i < mesh.parallel.worldSize ; i++ ) {

	
    	status = fscanf(inFile, "%d", &mesh.parallel.shared[i] );

	status = fscanf(inFile, "%d", &mesh.parallel.shared[i] );
	

	mesh.parallel.sendGhosts[i] = (uint*)malloc( mesh.parallel.shared[i] * sizeof(uint) );

	
    	for( j = 0 ; j < mesh.parallel.shared[i] ; j++ ) {

    	    status = fscanf( inFile, "%d", &mesh.parallel.sendGhosts[i][j] );

    	}

    }

    
    fclose(inFile);



    // Resize mpi send buffer

    mesh.parallel.sbuf = (double**)malloc( mesh.parallel.worldSize * sizeof(double*) );

    mesh.parallel.vsbuf = (double**)malloc( mesh.parallel.worldSize * sizeof(double*) );
    
    for( i = 0 ; i < mesh.parallel.worldSize ; i++ ) {

	mesh.parallel.sbuf[i] = (double*)malloc( mesh.parallel.shared[i] * mesh.mesh.Q * sizeof(double) );

	mesh.parallel.vsbuf[i] = (double*)malloc( mesh.parallel.shared[i] * 3 * sizeof(double) );

    }

    

    
    

    if (status) {}
    
    
    return mesh;
    
}
