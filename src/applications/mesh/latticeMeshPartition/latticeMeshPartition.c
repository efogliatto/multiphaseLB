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


    // Local mesh creation
    uint pid;
    for( pid = 0 ; pid < np ; pid++) {

	
	// Basic info
	
	struct latticeMesh localMesh;

	localMesh.parallel.pid = pid;

	localMesh.parallel.worldSize = np;

	localMesh.parallel.nlocal = nGhosts[pid][0];
	
	localMesh.parallel.nghosts = nGhosts[pid][1];


	
	// Check for shared elements

	uint i;
	for( i = 0 ; i < mesh.nPoints ; i++ ) {

	    if( local[i][pid] >= nGhosts[pid][0] ) {

		shared[pid][ owner[i] ]++;
		
	    }

	}


	// Resize index array and copy indices

	localMesh.parallel.shared        = (int*)malloc( np * sizeof(int) );
	localMesh.parallel.ghostsPerProc = (uint**)malloc( np * sizeof(uint*) );	
	
	for( i = 0 ; i < np ; i++ ) {

	    localMesh.parallel.shared[ owner[i] ] = 0;
	    
	    localMesh.parallel.ghostsPerProc[i] = (uint*)malloc( shared[pid][i] * sizeof(uint) );	    

	}


	
	// Move again and assign indices
	for( i = 0 ; i < mesh.nPoints ; i++ ) {

	    if( local[i][pid] >= nGhosts[pid][0] ) {

		localMesh.parallel.ghostsPerProc[ owner[i] ][  localMesh.parallel.shared[ owner[i] ]  ]  =  local[i][pid];

		localMesh.parallel.shared[ owner[i] ]++;
		
	    }

	}


    /* uint ii,jj; */
    /* if(pid==1) { */
    /* for(ii = 0 ; ii < np ; ii++) { */

    /* 	/\* for(jj = 0 ; jj < np ; jj++) { *\/ */

    /* 	/\*     printf("%d ",shared[ii][jj]); *\/ */

    /* 	/\* } *\/ */

    /* 	/\* printf("\n"); *\/ */

    /* 	printf("%d\n",localMesh.parallel.shared[ii]); */

    /* } */

    /* } */
	

    }




    /* uint ii,jj; */
    /* for(ii = 0 ; ii < np ; ii++) { */

    /* 	/\* for(jj = 0 ; jj < np ; jj++) { *\/ */

    /* 	/\*     printf("%d ",shared[ii][jj]); *\/ */

    /* 	/\* } *\/ */

    /* 	/\* printf("\n"); *\/ */

    /* 	printf("%d\n",localMesh.parallel.shared[ii]); */

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
