/*

  latticeMeshPartition

  Mesh subdivision for parallel processing

 */


#include <io.h>
#include <dictIO.h>
#include <latticeModel.h>
#include <basic.h>
#include <writeLatticeMesh.h>


// Standard decomposition
void standardDecomp( unsigned int* owner, basicMesh* mesh, unsigned int np );

// kmetis decomposition
void kmetisDecomp( unsigned int* owner, basicMesh* mesh, unsigned int np );

// Local Indexing
void localIndexing ( basicMesh* mesh, int** local, int** nGhosts, uint* owner, uint np );




int main(int argc, char** argv) {


    
 
    printf("\n  MESH PARTITIONING\n\n");

    unsigned int status;


    // Read full mesh

    basicMesh mesh = readBasicMesh();
    

    // Total number of processes

    unsigned int np = 1;

    double dn = 4;
    
    if( lookUpScalarEntry("properties/parallel","numProc",4, &dn) )
	np = (uint)dn;
    

    // Decomposition method
    
    char* method;
    
    status = lookUpStringEntry("properties/parallel","method",&method, "standard");

    if(status) {}

    
    
    
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

    	if( strcmp(method, "kmetis") == 0 ) {

    	    kmetisDecomp( owner, &mesh, np );
	
    	}

    	else {

    	    printf("\n\n  [ERROR]  Unable to recognize decomposition method \"%s\"\n\n\n",method);

    	    exit(1);

    	}

    }





    // Resize local indices array
    int** local   = matrixIntAlloc( mesh.nPoints, np, -1);
    int** nGhosts = matrixIntAlloc( np, 2, -1);
    /* int** shared  = matrixIntAlloc( np, np, 0); */
    int** nrecv  = matrixIntAlloc( np, np, 0);
    int** nsend  = matrixIntAlloc( np, np, 0);

    
    // Creation of local indexing
    localIndexing( &mesh, local, nGhosts, owner, np );


    // Total number of shared nodes
    uint i,
    	 pid;
    
    /* for( i = 0 ; i < mesh.nPoints ; i++ ) { */

    /* 	for( pid = 0 ; pid < np ; pid++) { */
	    
    /* 	    if( local[i][pid] >= nGhosts[pid][0] ) { */

    /* 		shared[pid][ owner[i] ]++; */

    /* 	    } */

    /* 	} */

    /* } */



    // Individual send and receive ghosts

    for( i = 0 ; i < mesh.nPoints ; i++ ) {

    	for( pid = 0 ; pid < np ; pid++) {
	    
    	    if( local[i][pid] >= nGhosts[pid][0] ) {


    		uint jj = owner[i];

    		nrecv[jj][pid]++;

    		nsend[pid][jj]++;
		

    	    }

    	}

    }




    /* for( i = 0 ; i < np ; i++ ) { */

    /* 	for( pid = 0 ; pid < np ; pid++) { */

    /* 	    printf("%d ", nrecv[i][pid]); */

    /* 	} */

    /* 	printf("\n"); */

    /* } */
    
    /* printf("\n\n"); */
    
    /* for( i = 0 ; i < np ; i++ ) { */

    /* 	for( pid = 0 ; pid < np ; pid++) { */

    /* 	    printf("%d ", nsend[i][pid]); */

    /* 	} */

    /* 	printf("\n"); */

    /* } */
    
    
    
    // Local mesh creation
    latticeMesh* localMesh = (latticeMesh*)malloc( np * sizeof(latticeMesh) );

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



    	    /* // Add sharing info and resize elements */
	    
    	    /* localMesh[rpid].parallel.shared = (uint*)malloc( np * sizeof(uint) ); */

    	    /* for( spid = 0 ; spid < np ; spid++ ) { */

    	    /* 	localMesh[rpid].parallel.shared[spid] = shared[rpid][spid]; */

    	    /* } */


    	    // Add sharing info and resize elements
	    
    	    localMesh[rpid].parallel.nrg = (uint*)malloc( np * sizeof(uint) );

    	    localMesh[rpid].parallel.nsg = (uint*)malloc( np * sizeof(uint) );

    	    for( spid = 0 ; spid < np ; spid++ ) {

    		localMesh[rpid].parallel.nrg[spid] = nrecv[spid][rpid];

    		localMesh[rpid].parallel.nsg[spid] = nsend[spid][rpid];

    	    }


    	    // Resize ghost info
	    
    	    localMesh[rpid].parallel.recvGhosts = (uint**)malloc( np * sizeof(uint*) );

    	    localMesh[rpid].parallel.sendGhosts = (uint**)malloc( np * sizeof(uint*) );
	    
    	    for( spid = 0 ; spid < np ; spid++ ) {

    		localMesh[rpid].parallel.recvGhosts[spid] = (uint*)malloc( nrecv[spid][rpid] * sizeof(uint) );

    		localMesh[rpid].parallel.sendGhosts[spid] = (uint*)malloc( nsend[spid][rpid] * sizeof(uint) );
		
    	    }




    	    // Add points. First local, then ghost

    	    localMesh[rpid].mesh.nPoints = localMesh[rpid].parallel.nlocal + localMesh[rpid].parallel.nghosts;
	    
    	    localMesh[rpid].mesh.points = matrixIntAlloc( localMesh[rpid].mesh.nPoints, 3, 0 );

    	    for( i = 0 ; i < mesh.nPoints ; i++ ) {

    		int lid = local[i][rpid];
		
    		if( lid != -1 ) {

    		    localMesh[rpid].mesh.points[lid][0] = mesh.points[i][0];
    		    localMesh[rpid].mesh.points[lid][1] = mesh.points[i][1];
    		    localMesh[rpid].mesh.points[lid][2] = mesh.points[i][2];
		    
    		}

    	    }



    	    // Add Neighbours.
	    
    	    localMesh[rpid].mesh.nb = matrixIntAlloc( localMesh[rpid].parallel.nlocal, mesh.Q, -1 );

    	    localMesh[rpid].mesh.Q = mesh.Q;

    	    for( i = 0 ; i < mesh.nPoints ; i++ ) {

    		int lid = local[i][rpid];
		
    		if( lid < localMesh[rpid].parallel.nlocal ) {


    		    // Move over velocities

    		    uint velId;
    		    int nbid;

    		    for( velId = 0 ; velId < mesh.Q ; velId++ ) {

    			nbid = mesh.nb[i][velId];

    			if( nbid != -1 ) {
			    
    			    localMesh[rpid].mesh.nb[lid][velId] = local[nbid][rpid];

    			}

    		    }
		    
		    
    		}

    	    }







    	    // Add vtkCells

    	    localMesh[rpid].mesh.ncells = 0;
	    
    	    for( i = 0 ; i < mesh.ncells ; i++ ) {

    		uint cid,
    		     find = 0;

    		for( cid = 0 ; cid < mesh.cellType ; cid++ ) {

    		    // Check if all members are local
    		    if( local[ mesh.vtkCells[i][cid] ][rpid] == -1 ) {

    			find++;

    		    }

    		}

    		if( find == 0 ) {

    		    localMesh[rpid].mesh.ncells++;

    		}

    	    }



    	    // Resize and add

    	    localMesh[rpid].mesh.cellType = mesh.cellType;
	    
    	    localMesh[rpid].mesh.vtkCells = matrixIntAlloc( localMesh[rpid].mesh.ncells, mesh.cellType, -1);

    	    uint count = 0;
	    
    	    for( i = 0 ; i < mesh.ncells ; i++ ) {

    		uint cid,
    		     find = 0;

    		for( cid = 0 ; cid < mesh.cellType ; cid++ ) {

    		    // Check if all members are local
    		    if( local[ mesh.vtkCells[i][cid] ][rpid] == -1 ) {

    			find++;

    		    }

    		}

    		if( find == 0 ) {

		    
    		    for( cid = 0 ; cid < mesh.cellType ; cid++ ) {

    			localMesh[rpid].mesh.vtkCells[count][cid] = local[ mesh.vtkCells[i][cid] ][rpid];

    		    }
		    
		    
    		    count++;

    		}

    	    }








    	    // Boundaries. Assign boundaries from original mesh

    	    localMesh[rpid].mesh.bd.nbd = mesh.bd.nbd;
	    
    	    localMesh[rpid].mesh.bd.nbdelem = (uint*)malloc( mesh.bd.nbd * sizeof(uint) );

    	    localMesh[rpid].mesh.bd.bdPoints = (uint**)malloc( mesh.bd.nbd * sizeof(uint*) );

    	    for( i = 0 ; i < localMesh[rpid].mesh.bd.nbd ; i++ ) {

    		localMesh[rpid].mesh.bd.nbdelem[i] = 0;

    		sprintf( localMesh[rpid].mesh.bd.bdNames[i], "%s", mesh.bd.bdNames[i] );

    		uint bdpid;

    		for( bdpid = 0 ; bdpid < mesh.bd.nbdelem[i] ; bdpid++ ) {

    		    if( local[ mesh.bd.bdPoints[i][bdpid] ][rpid] < localMesh[rpid].parallel.nlocal ) {

    			localMesh[rpid].mesh.bd.nbdelem[i]++;

    		    }

    		}

    	    }


	    
	    
	    
    	    for( i = 0 ; i < localMesh[rpid].mesh.bd.nbd ; i++ ) {

    		count = 0;
		
    	    	localMesh[rpid].mesh.bd.bdPoints[i] = (uint*)malloc( localMesh[rpid].mesh.bd.nbdelem[i] * sizeof(uint) );

    	    	uint bdpid;

    	    	for( bdpid = 0 ; bdpid < mesh.bd.nbdelem[i] ; bdpid++ ) {

    	    	    if( local[ mesh.bd.bdPoints[i][bdpid] ][rpid] < localMesh[rpid].parallel.nlocal ) {

    	    		localMesh[rpid].mesh.bd.bdPoints[i][count] = local[ mesh.bd.bdPoints[i][bdpid] ][rpid];

    	    		count++;

    	    	    }

    	    	}

    	    }




	    
	    
	    

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






	
	
    }




    


    // Write lattice meshes
    {

    	int status = system( "rm -rf processor*" );

    	if (!status) {

    	    for( i = 0 ; i < np ; i++ ) {

    		writeLatticeMesh( &localMesh[i] );

    	    }

    	}
    }

    

    



    printf("Finished domain decomposition\n\n");
    
    
    return 0;

}
