/*

  latticeMeshPartition

  Mesh subdivision for parallel processing

 */


#include <io.h>
#include <latticeModel.h>
#include <basic.h>
#include <latticeMesh.h>


// Standard decomposition
void standardDecomp( unsigned int* owner, struct basicMesh* mesh, unsigned int np );

// Local Indexing
void localIndexing ( struct basicMesh* mesh, int** local, int** nGhosts, uint* owner, uint np );




int main(int argc, char** argv) {


    
 
    printf("\n  MESH PARTITIONING\n\n");


    // Read full mesh
    struct basicMesh mesh = readBasicMesh();
    

    // Total number of processes
    uint np = (uint)lookUpDoubleEntry("properties/parallel","numProc",4);

    // Decomposition method
    char method[100];
    lookUpStringEntry("properties/parallel","method",method);



    
    
    
    // ******************************************************************** //
    //                             Processors                               //
    // ******************************************************************** //


    printf("Decomposing domain\n\n");

    // Ownership array
    uint* owner = (uint*)malloc( mesh.nPoints * sizeof(uint) );

    // Choose decomposition method
    if( strcmp(method, "standard") == 0 ) {

	standardDecomp( owner, &mesh, np );

    }

    else {

	printf("\n\n  [ERROR]  Unable to recognize decomposition method \"%s\"\n\n\n",method);

	exit(1);

    }





    // Resize local indices array
    int** local   = matrixIntAlloc( mesh.nPoints, np, -1);
    int** nGhosts = matrixIntAlloc( np, 2, -1);
    int** shared  = matrixIntAlloc( np, np, 0);

    
    // Creation of local indexing
    localIndexing( &mesh, local, nGhosts, owner, np );


    // Total number of shared nodes
    uint i,
	 pid;
    
    for( i = 0 ; i < mesh.nPoints ; i++ ) {

	for( pid = 0 ; pid < np ; pid++) {

	    if( local[i][pid] >= nGhosts[pid][0] ) {

		shared[pid][ owner[i] ]++;

	    }

	}

    }


    // Local mesh creation
    struct latticeMesh* localMesh = (struct latticeMesh*)malloc( np * sizeof(struct latticeMesh) );

    // Move over meshes and look for recv ghosts
    {

	
	uint rpid,spid;

	// Counter arrays
	int** gcount = matrixIntAlloc( np, np, 0);
	

	// Move over recv lattices. Basic info and resize arrays
	
	for( rpid = 0 ; rpid < np ; rpid++ ) {


	    // Add basic info
	    
	    localMesh[rpid].parallel.pid = rpid;

	    localMesh[rpid].parallel.worldSize = np;

	    localMesh[rpid].parallel.nlocal = nGhosts[rpid][0];
	
	    localMesh[rpid].parallel.nghosts = nGhosts[rpid][1];



	    // Add sharing info and resize elements
	    
	    localMesh[rpid].parallel.shared = (uint*)malloc( np * sizeof(uint) );

	    for( spid = 0 ; spid < np ; spid++ ) {

		localMesh[rpid].parallel.shared[spid] = shared[rpid][spid];

	    }


	    // Resize ghost info
	    
	    localMesh[rpid].parallel.recvGhosts = (uint**)malloc( np * sizeof(uint*) );

	    localMesh[rpid].parallel.sendGhosts = (uint**)malloc( np * sizeof(uint*) );
	    
	    for( spid = 0 ; spid < np ; spid++ ) {

		localMesh[rpid].parallel.recvGhosts[spid] = (uint*)malloc( shared[rpid][spid] * sizeof(uint) );

		localMesh[rpid].parallel.sendGhosts[spid] = (uint*)malloc( shared[rpid][spid] * sizeof(uint) );
		
	    }




	    // Add points. First local, then ghost

	    
	    

	}







	// Move over local lattices and add parallel info

	for( i = 0 ; i < mesh.nPoints ; i++ ) {
	
	    for( rpid = 0 ; rpid < np ; rpid++ ) {

		if( local[i][rpid] >= nGhosts[rpid][0] ) {


		    // Add local index as recv ghost

		    spid = owner[i];
		    
		    localMesh[rpid].parallel.recvGhosts[ spid ][ gcount[rpid][spid] ]   =  local[i][rpid];


		    // Add local index as send ghost
		    
		    localMesh[spid].parallel.sendGhosts[ rpid ][ gcount[rpid][spid] ]   =  local[i][spid];

		    gcount[rpid][spid]++;

		}
	    
	    }

	}



	/* uint ii,jj; */

	/* for(ii = 0 ; ii < np ; ii++) { */

	/*     for(jj = 0 ; jj < np ; jj++) { */

	/*         printf("%d ",gcount[ii][jj]); */

	/*     } */

	/*     printf("\n"); */


	/* } */



	
	
    }




    

    

    

    


    
    
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
