/*

  latticeMeshPartition

  Mesh subdivision for parallel processing

 */


#include <io.h>
#include <latticeModel.h>
#include <basic.h>


int main(int argc, char** argv) {


    
    // ******************************************************************** //
    //                            Program options                           //
    // ******************************************************************** //

    // Total number of processes
    unsigned int np = 1;
    {

    	unsigned int arg;

    	for(arg = 0 ; arg < argc ; arg++) {

    	    if( strcmp("--np", argv[arg]) == 0 ) {

    	    	np = atoi( argv[arg+1] );

    	    }

    	}
	
    }
    



    
 
    printf("\nMESH PARTITIONING\n\n");

    
    

    // ******************************************************************** //
    //                         Points inside geometry                       //
    // ******************************************************************** //

    printf("Reading Mesh points\n\n");

    // Open file
    /* FILE* inFile; */
    /* openFile(inFile, "lattice/points", "r"); */
    FILE* inFile = fopen( "lattice/points", "r" );
    

    // Number of points
    uint npoints;
    fscanf(inFile, "%d", &npoints);

    // Read Mesh points
    int** meshPoints = matrixIntAlloc(npoints,3,0);
    uint i,j;
    for( i = 0 ; i < npoints ; i++ ) {

	fscanf(inFile, "%d", &meshPoints[i][0]);
	fscanf(inFile, "%d", &meshPoints[i][1]);
	fscanf(inFile, "%d", &meshPoints[i][2]);

    }

    fclose(inFile);



    


    // ******************************************************************** //
    //                             Neighbours                               //
    // ******************************************************************** //

    printf("Reading Neighbour indices\n\n");

    // Open file
    inFile = fopen( "lattice/neighbours", "r" );

    // Lattice Model
    char lbm[100];
    lookUpStringEntry("properties/latticeProperties","LBModel",lbm);

    // Read neighbours
    int** neigh = matrixIntAlloc(npoints, latticeQ(lbm), -1);
    for( i = 0 ; i < npoints ; i++ ) {

	for( j = 0 ; j < latticeQ(lbm) ; j++ ) {

	    fscanf(inFile, "%d", &neigh[i][j]);

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
    uint ncells, ctype;
    fscanf(inFile, "%d", &ncells);
    fscanf(inFile, "%d", &ctype);
    
    // Read cells
    int** vtkCells = matrixIntAlloc(ncells, ctype, -1);
    for( i = 0 ; i < ncells ; i++ ) {

	for( j = 0 ; j < ctype ; j++ ) {

	    fscanf(inFile, "%d", &vtkCells[i][j]);

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
    uint nbd;
    fscanf(inFile, "%d\n", &nbd);

    // Total number of elements per boundary type
    uint* nbdelem = (uint*)malloc(nbd * sizeof(uint));

    // Boundary names (max 100 boundaries)
    char bdNames[100][100];
    

    // Elements in boundary
    uint** bdPoints = (uint**)malloc( nbd * sizeof(uint*) );
    

    // Read boundary
    for( i = 0 ; i < nbd ; i++ ) {

    	// Boundary name
	fscanf(inFile, "%s", bdNames[i]);

    	// Elements in boundary
    	fscanf(inFile, "%d", &nbdelem[i]);

    	// Resize bdPoints
    	bdPoints[i] = (uint*)malloc( nbdelem[i] * sizeof(uint) );
	
    	for( j = 0 ; j < nbdelem[i] ; j++ ) {

    	    fscanf(inFile, "%d", &bdPoints[i][j]);

    	}

    }





    






    
    
    
    /* // ******************************************************************** // */
    /* //                             Processors                               // */
    /* // ******************************************************************** // */


    /* cout << "Decomposing domain" << endl; */


    /* // Split on processors */
    /* const uint np = vm["processors"].as<int>(); */
    /* vector<uint> procBegin(np), */
    /* 	procEnd(np); */

    /* for(uint i = 0 ; i < np ; i++ ) { */
    /* 	if(i != 0) { */
    /* 	    procBegin[i] = procEnd[i-1] + 1; */
    /* 	    procEnd[i] = procBegin[i] + (int)(meshPoints.size()/np) - 1; */
    /* 	} */
    /* 	else { */
    /* 	    procBegin[i] = 0; */
    /* 	    procEnd[0] = (int)(meshPoints.size()/np) - 1; */
    /* 	} */
    /* } */
    /* procEnd[np - 1] = meshPoints.size() - 1; */

    
    /* // Ownership vector */
    /* vector<uint> owner; */
    /* owner.resize( meshPoints.size() ); */

    /* for(uint pid = 0 ; pid < np ; pid++) { */
    /* 	for(uint i = procBegin[pid] ; i <= procEnd[pid] ; i++) { */
    /* 	    owner[i] = pid; */
    /* 	} */
    /* } */

    
    /* // Create set of IOPatchs, according to number of processors */
    /* vector< IOPatch<Vector3> > patches; */

    /* for(uint pid = 0 ; pid < np ; pid++) */
    /* 	patches.push_back( IOPatch<Vector3>(lbm) ); */

    /* // Set patch indices */
    /* for(uint pid = 0 ; pid < np ; pid++) */
    /* 	patches[pid].setId(pid); */

    /* // Assign neighbours */
    /* for(vector< IOPatch<Vector3> >::iterator it = patches.begin() ; it != patches.end() ; it++) */
    /* 	it->setGlobalNeighbours( neigh, owner ); */

    /* // Assign values */
    /* for(vector< IOPatch<Vector3> >::iterator it = patches.begin() ; it != patches.end() ; it++) */
    /* 	it->setValues( meshPoints );         */


    /* // Set send maps */
    /* for(uint i = 0 ; i < patches.size() ; i++) { */

    /* 	for(uint j = 0 ; j < patches.size() ; j++) { */

    /* 	    if( i != j ) { */

    /* 		patches[i].setSendMap( patches[j].id(), patches[j].ghostRecvGId( patches[i].id() ) ); */
		
    /* 	    } */
	    
    /* 	} */
	
    /* }     */


    /* // Assign boundary elements */
    /* for(vector< IOPatch<Vector3> >::iterator it = patches.begin() ; it != patches.end() ; it++) */
    /* 	it->setGlobalBdMap( globalBmap ); */
    
    

    /* // Write patch information */
    /* for(uint pid = 0 ; pid < patches.size() ; pid++) { */

    /* 	cout << "    processor" << pid << endl;  */

    /* 	ostringstream folderName; */
    /* 	folderName << "processor" << pid << "/" << vm["DQmodel"].as<string>() << "_lattice"; */

    /* 	// Neighbours */
    /* 	patches[pid].writeNeighboursIds(  "neighbours", folderName.str() ); */

    /* 	// Global Ids, local nodes */
    /* 	patches[pid].writeGlobalIdLocal(  "globalIds", folderName.str() ); */

    /* 	// Global indices, ghost nodes */
    /* 	patches[pid].writeGlobalIdGhost(  "globalGhostsIds", folderName.str() );	 */

    /* 	// Recv map indices */
    /* 	patches[pid].writeRecvMapsIds(  "recvMapIds", folderName.str() ); */

    /* 	// Send map indices */
    /* 	patches[pid].writeSendMapsIds(  "sendMapIds", folderName.str() ); */

    /* 	// Local and ghost values */
    /* 	patches[pid].writeAllValues(  "points", folderName.str() ); */

    /* 	// VTK Cells */
    /* 	patches[pid].writeVTKCells(  "vtkCells", folderName.str(), vtkCells ); */

    /* 	// Boundary elements */
    /* 	patches[pid].writeBoundariesIds(  "boundary", folderName.str() ); */
	
    /* } */

    /* cout << endl << "Finished domain decomposition" << endl << endl; */
    
    
    return 0;

}
