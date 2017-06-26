/*

  latticeMeshPartition

  Mesh subdivision for parallel processing

 */


#include <io.h>
#include <latticeModel.h>
#include <basic.h>
#include <basicMesh.h>


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
    



    
 
    printf("\n  MESH PARTITIONING\n\n");


    // Read full mesh
    struct basicMesh mesh = readBasicMesh();
    





    
    
    
    /* // ******************************************************************** // */
    /* //                             Processors                               // */
    /* // ******************************************************************** // */


    /* printf("Decomposing domain\n\n"); */

    /* uint* procBegin = (uint*)malloc( np * sizeof(uint) ); */
    /* uint* procEnd   = (uint*)malloc( np * sizeof(uint) ); */

    /* // Split on processors */
    /* for( i = 0 ; i < np ; i++ ) { */
	
    /* 	if(i != 0) { */
	    
    /* 	    procBegin[i] = procEnd[i-1] + 1; */
    /* 	    procEnd[i] = procBegin[i] + (int)(npoints/np) - 1; */
	    
    /* 	} */
	
    /* 	else { */
	    
    /* 	    procBegin[i] = 0; */
    /* 	    procEnd[0] = (int)(npoints/np) - 1; */
	    
    /* 	} */
	
    /* } */
    
    /* procEnd[np - 1] = npoints - 1; */

    

    
    /* // Ownership vector */
    /* uint* owner = (uint*)malloc( npoints * sizeof(uint) ); */
    
    /* uint pid; */
    /* for( pid = 0 ; pid < np ; pid++ ) { */
	
    /* 	for( i = procBegin[pid] ; i <= procEnd[pid] ; i++ ) { */
	    
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
