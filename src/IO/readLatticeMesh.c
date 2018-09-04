#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <latticeMesh.h>
#include <basic.h>
#include <io.h>
#include <latticeModel.h>

latticeMesh readLatticeMesh( uint pid ) {

    
    
    latticeMesh mesh;

    uint i,j,status;

    char command[100];

    FILE* inFile;

    

    
    // Basic information

    mesh.parallel.pid = pid;


    // Time information
    
    readTimeInfo( &mesh );


    // Update lattice properties

    mesh.lattice = setLatticeInfo();

    

    

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


    

    if(status) {}



    

    // ******************************************************************** //
    //                             Neighbours                               //
    // ******************************************************************** //


    mesh.mesh.Q = mesh.lattice.Q;
    
    if(  !int2dArray( &mesh.mesh.nb, mesh.parallel.nlocal, mesh.mesh.Q, -1 )  )
	errorMsg("Unable to allocate memory for neighbours");


    
    
    sprintf(command,"processor%d/lattice/neighbours", pid);

    inFile = fopen( command, "r" );

    for( i = 0 ; i < mesh.parallel.nlocal ; i++ ) {

    	for( j = 0 ; j < mesh.mesh.Q ; j++ ) {

    	    status = fscanf(inFile, "%d", &mesh.mesh.nb[i][j]);

    	}

    }

    fclose(inFile);    




    // Check if node is on boundary

    mesh.mesh.isOnBnd = (uint*)malloc( mesh.parallel.nlocal * sizeof(uint) );

    for( i = 0 ; i < mesh.parallel.nlocal ; i++ ) {

        uint is_bnb = 0;	
      
    	for( j = 0 ; j < mesh.mesh.Q ; j++ ) {

	    if( mesh.mesh.nb[i][j] == -1 ) {

		is_bnb++;

	    }

    	}



	if(is_bnb == 0) {

	    mesh.mesh.isOnBnd[i] = 0;

	}

	else {

	    mesh.mesh.isOnBnd[i] = 1;

	}

	

    }
    
    
    

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

    mesh.parallel.nrg        = (uint*)malloc( mesh.parallel.worldSize * sizeof(uint) );

    mesh.parallel.recvGhosts = (uint**)malloc( mesh.parallel.worldSize * sizeof(uint*) );
    
   
    
    for( i = 0 ; i < mesh.parallel.worldSize ; i++ ) {

    	uint auxPid;
	
    	status = fscanf(inFile, "%d", &auxPid );


    	if( auxPid == i ) {
	

    	    status = fscanf(inFile, "%d", &mesh.parallel.nrg[i] );
	
    	    mesh.parallel.recvGhosts[i] = (uint*)malloc( mesh.parallel.nrg[i] * sizeof(uint) );

	
    	    for( j = 0 ; j < mesh.parallel.nrg[i] ; j++ ) {

    		status = fscanf( inFile, "%d", &mesh.parallel.recvGhosts[i][j] );

    	    }

	    
    	}

    }

    
    fclose(inFile);



    // Resize mpi recv buffer

    mesh.parallel.rbuf = (scalar**)malloc( mesh.parallel.worldSize * sizeof(scalar*) );

    mesh.parallel.vrbuf = (scalar**)malloc( mesh.parallel.worldSize * sizeof(scalar*) );
    
    for( i = 0 ; i < mesh.parallel.worldSize ; i++ ) {

    	mesh.parallel.rbuf[i] = (scalar*)malloc( mesh.parallel.nrg[i] * mesh.mesh.Q * sizeof(scalar) );

    	mesh.parallel.vrbuf[i] = (scalar*)malloc( mesh.parallel.nrg[i] * 3 * sizeof(scalar) );

    }








    // ******************************************************************** //
    //                                Send Ghosts                           //
    // ******************************************************************** //

    
    sprintf(command,"processor%d/lattice/sendGhosts", pid);

    inFile = fopen( command, "r" );

  
    status = fscanf(inFile, "%d\n", &mesh.parallel.worldSize);

    mesh.parallel.nsg        = (uint*)malloc( mesh.parallel.worldSize * sizeof(uint) );
    
    mesh.parallel.sendGhosts = (uint**)malloc( mesh.parallel.worldSize * sizeof(uint*) );
    
   
    
    for( i = 0 ; i < mesh.parallel.worldSize ; i++ ) {

    	uint auxPid;
	
    	status = fscanf(inFile, "%d", &auxPid );


    	if( auxPid == i ) {

    	    status = fscanf(inFile, "%d", &mesh.parallel.nsg[i] );
	
    	    mesh.parallel.sendGhosts[i] = (uint*)malloc( mesh.parallel.nsg[i] * sizeof(uint) );

	
    	    for( j = 0 ; j < mesh.parallel.nsg[i] ; j++ ) {

    		status = fscanf( inFile, "%d", &mesh.parallel.sendGhosts[i][j] );

    	    }

    	}

    }

    
    fclose(inFile);



    // Resize mpi send buffer

    mesh.parallel.sbuf = (scalar**)malloc( mesh.parallel.worldSize * sizeof(scalar*) );

    mesh.parallel.vsbuf = (scalar**)malloc( mesh.parallel.worldSize * sizeof(scalar*) );
    
    for( i = 0 ; i < mesh.parallel.worldSize ; i++ ) {

    	mesh.parallel.sbuf[i] = (scalar*)malloc( mesh.parallel.nsg[i] * mesh.mesh.Q * sizeof(scalar) );

    	mesh.parallel.vsbuf[i] = (scalar*)malloc( mesh.parallel.nsg[i] * 3 * sizeof(scalar) );

    }

    






    // Total number of elements per patch

    mesh.parallel.nodesPerPatch = (uint*)malloc( mesh.parallel.worldSize * sizeof(uint) );

    for( i = 0 ; i < mesh.parallel.worldSize ; i++ ) {

	uint npp = 0;
	
	sprintf(command,"processor%d/lattice/points", i);

	inFile = fopen( command, "r" );

	fscanf(inFile, "%d", &npp);

	fclose(inFile);

	mesh.parallel.nodesPerPatch[i] = npp;

	

	sprintf(command,"processor%d/lattice/ghosts", i);

	inFile = fopen( command, "r" );

	fscanf(inFile, "%d", &npp);

	fclose(inFile);

	mesh.parallel.nodesPerPatch[i] += npp;
	

    }

    






    // Nodes level

    mesh.parallel.level = (uint*)malloc( mesh.mesh.nPoints * sizeof(uint) );

    
    // Level 4
    
    for( i = 0 ; i < mesh.mesh.nPoints ; i++ )
    	mesh.parallel.level[i] = 4;

    
    // Level 0
    
    for( i = mesh.parallel.nlocal ; i < mesh.mesh.nPoints ; i++ )
    	mesh.parallel.level[i] = 0;


    // Level 1
    
    for( i = 0 ; i < mesh.parallel.nlocal ; i++ ) {

    	for( j = 1 ; j < mesh.mesh.Q ; j++ ) {

    	    int nb = mesh.mesh.nb[i][j];

    	    if( nb != -1 ) {
	    
    		if( mesh.parallel.level[nb] == 0 ) {

    		    mesh.parallel.level[i] = 1;

    		}

    	    }

    	}

    }




    // Level 2
    
    for( i = 0 ; i < mesh.parallel.nlocal ; i++ ) {
	
    	for( j = 1 ; j < mesh.mesh.Q ; j++ ) {

    	    int nb = mesh.mesh.nb[i][j];

    	    if( nb != -1 ) {
	    
    		if(  ( mesh.parallel.level[nb] == 1 )   &&   ( mesh.parallel.level[i] == 4 )  ){

    		    mesh.parallel.level[i] = 2;

    		}

    	    }

    	}

    }
    



    // Level 3
    
    for( i = 0 ; i < mesh.parallel.nlocal ; i++ ) {
	
    	for( j = 1 ; j < mesh.mesh.Q ; j++ ) {

    	    int nb = mesh.mesh.nb[i][j];

    	    if( nb != -1 ) {
	    
    		if(  ( mesh.parallel.level[nb] == 2 )   &&   ( mesh.parallel.level[i] == 4 )  ){

    		    mesh.parallel.level[i] = 3;

    		}

    	    }

    	}

    }
    
    

    if (status) {}
    
    
    return mesh;
    
}
