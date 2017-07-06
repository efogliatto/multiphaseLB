#include <stdlib.h>
#include <stdio.h>
#include <latticeMesh.h>
#include <mpi.h>
#include <math.h>


void syncVectorField( struct latticeMesh* mesh, double** fld ) {


    if( mesh->parallel.worldSize > 1 ) {

	
    	MPI_Barrier(MPI_COMM_WORLD);

	

	// Move over send ghosts. Copy data to buffer

	unsigned int pid;

	for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {


	    unsigned int i, k, id;

	    for( i = 0 ; i < mesh->parallel.shared[pid] ; i++) {

		for( k = 0 ; k < 3 ; k++ ) {


		    // Position in sbuf

		    id = i*3 + k;

		    
		    // Copy field info
		    
		    mesh->parallel.vsbuf[pid][id] = fld[ mesh->parallel.sendGhosts[pid][i] ][ k ];
		    

		}

	    }
	  

	}




    	// Send information
    	
    	MPI_Status status[100];

	MPI_Request request[100];

	int nreq = 0;

	
	// Move over send ghosts. Send data

	for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {

	    if( mesh->parallel.shared[pid] > 0 ) {
	    
		MPI_Isend (&mesh->parallel.vsbuf[pid][0], mesh->parallel.shared[pid] * 3, MPI_DOUBLE, pid, mesh->parallel.pid, MPI_COMM_WORLD, &request[nreq]);

		nreq++;

	    }
	}



	// Move over recv ghosts. Receive data

	for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {

	    if( mesh->parallel.shared[pid] > 0 ) {
	    
		MPI_Irecv (mesh->parallel.vrbuf[pid], mesh->parallel.shared[pid] * 3, MPI_DOUBLE, pid, pid, MPI_COMM_WORLD, &request[nreq]);

		nreq++;

	    }
	}


	
	// Wait for everyone

	MPI_Waitall(nreq, request, status);




	
	/* // Blocking communications */

	/* // Move over send ghosts. Send data */

    	/* MPI_Status status; */

	/* for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) { */

	/*     if( mesh->parallel.shared[pid] > 0 ) { */
	    
	/* 	MPI_Send (&mesh->parallel.vsbuf[pid][0], mesh->parallel.shared[pid] * 3, MPI_DOUBLE, pid, mesh->parallel.pid, MPI_COMM_WORLD); */

	/*     } */
	/* } */



	/* // Wait for everyone */
	
	/* MPI_Barrier(MPI_COMM_WORLD); */
	

	
	/* // Move over recv ghosts. Receive data */

	/* for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) { */

	/*     if( mesh->parallel.shared[pid] > 0 ) { */
	    
	/* 	MPI_Recv (mesh->parallel.vrbuf[pid], mesh->parallel.shared[pid] * 3, MPI_DOUBLE, pid, pid, MPI_COMM_WORLD, &status); */
		
	/*     } */
	/* } */



	/* // Wait for everyone */
	
	/* MPI_Barrier(MPI_COMM_WORLD); */

	








	

	// Copy new data back to ghost nodes

	for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {

	    
	    unsigned int i, k, id;

	    for( i = 0 ; i < mesh->parallel.shared[pid] ; i++) {

		for( k = 0 ; k < 3 ; k++ ) {


		    // Position in sbuf

		    id = i*3 + k;

		    
		    // Copy field info
		    
		    fld[ mesh->parallel.recvGhosts[pid][i] ][ k ] = mesh->parallel.vrbuf[pid][id];
		    

		}

	    }		

	    
	}	
	
	

	// Wait for everyone
	
	MPI_Barrier(MPI_COMM_WORLD);

    }
	
}





















/* void syncPdfField( struct latticeMesh* mesh, double** fld ) { */


/*     if( mesh->parallel.worldSize > 1 ) { */

	
/*     	MPI_Barrier(MPI_COMM_WORLD); */

	
/*     	// Send information. Divide by blocks */

/*     	/\* MPI_Request request; *\/ */
/*     	MPI_Status status; */

	
    
/*     	// Send information. Divide by blocks and columns */

/*     	unsigned int k; */
	
/*     	for( k = 0 ; k < mesh->mesh.Q ; k++ ) { */

	    
/*     	    // Copy data to send buffer */
    
/*     	    // Move over send ghosts */

/* 	    unsigned int pid; */

/*     	    for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) { */

	
/*     /\* 		/\\* Move over blocks per send ghost *\\/ *\/ */
/*     /\* 		unsigned int bid; *\/ */
/*     /\* 		for( bid = 0 ; bid < info->sendScalarBlocks[pid] ; bid++ ) { *\/ */

/*     /\* 		    // Move inside blocks *\/ */
/*     /\* 		    unsigned int i, *\/ */
/*     /\* 			lid; *\/ */
	    
/*     /\* 		    for( i = 0 ; i < MPI_BUFF_SIZE ; i++ ) { *\/ */

/*     /\* 			// Local index inside processor list *\/ */
/*     /\* 			lid = bid * MPI_BUFF_SIZE + i; *\/ */
		
/*     /\* 			// Copy data *\/ */
/*     /\* 			if( lid < info->sendGhostIds[pid][1]) { *\/ */

/*     /\* 			    info->ssbuf[pid][lid] = fld[ info->sendGhostIds[pid][lid+2] ][k]; *\/ */

/*     /\* 			} *\/ */
		
/*     /\* 		    } *\/ */
	    
/*     /\* 		} *\/ */

/*     /\* 	    } *\/ */
	


    
/*     /\* 	    // Send data in send buffer *\/ */

    
/*     /\* 	    // Move over send ghosts *\/ */
/*     /\* 	    for( pid = 0 ; pid < info->nSendGhosts ; pid++ ) { *\/ */

/*     /\* 		// Move ovel blocks per send ghost *\/ */
/*     /\* 		unsigned int bid; *\/ */
/*     /\* 		for( bid = 0 ; bid < info->sendScalarBlocks[pid] ; bid++ ) { *\/ */

/*     /\* 		    // Start position of each block *\/ */
/*     /\* 		    unsigned int lid = bid * MPI_BUFF_SIZE; *\/ */

/*     /\* 		    // Send data. tag = bid *\/ */
/*     /\* 		    if(  bid != (info->sendScalarBlocks[pid] - 1)  ) { *\/ */
/*     /\* 			/\\* MPI_Isend (&info->parallel.ssbuf[pid][lid], MPI_BUFF_SIZE, MPI_DOUBLE, info->parallel.sendGhostIds[pid][0], bid, MPI_COMM_WORLD, &request); *\\/ *\/ */
/*     /\* 			MPI_Send (&info->ssbuf[pid][lid], MPI_BUFF_SIZE, MPI_DOUBLE, info->sendGhostIds[pid][0], bid, MPI_COMM_WORLD); *\/ */
/*     /\* 		    } *\/ */
/*     /\* 		    else { *\/ */

/*     /\* 			int msg = info->sendScalarBlocks[pid] * MPI_BUFF_SIZE - info->sendGhostIds[pid][1]; *\/ */
/*     /\* 			msg = MPI_BUFF_SIZE - msg; *\/ */
/*     /\* 			/\\* MPI_Isend (&info->parallel.ssbuf[pid][lid], msg, MPI_DOUBLE, info->parallel.sendGhostIds[pid][0], bid, MPI_COMM_WORLD, &request); *\\/ *\/ */
/*     /\* 			MPI_Send (&info->ssbuf[pid][lid], msg, MPI_DOUBLE, info->sendGhostIds[pid][0], bid, MPI_COMM_WORLD); *\/ */

/*     /\* 		    } *\/ */
	    
/*     /\* 		} *\/ */

/*     /\* 	    } *\/ */



/*     /\* 	    /\\* MPI_Barrier(MPI_COMM_WORLD); *\\/	 *\/ */


/*     /\* 	    // Receive data in recv buffer *\/ */
    
/*     /\* 	    // Move over recv ghosts *\/ */
/*     /\* 	    for( pid = 0 ; pid < info->nRecvGhosts ; pid++ ) { *\/ */

/*     /\* 		// Move ovel blocks per recv ghost *\/ */
/*     /\* 		unsigned int bid; *\/ */
/*     /\* 		for( bid = 0 ; bid < info->recvScalarBlocks[pid] ; bid++ ) { *\/ */

/*     /\* 		    // Start position of each block *\/ */
/*     /\* 		    unsigned int lid =  bid * MPI_BUFF_SIZE; *\/ */

/*     /\* 		    // Send data. tag = bid *\/ */
/*     /\* 		    if(  bid != (info->recvScalarBlocks[pid] - 1)  ) { *\/ */
/*     /\* 			/\\* MPI_Irecv (&info->parallel.srbuf[pid][lid], MPI_BUFF_SIZE, MPI_DOUBLE, info->parallel.recvGhostIds[pid][0], bid, MPI_COMM_WORLD, &request); *\\/ *\/ */
/*     /\* 			MPI_Recv (&info->srbuf[pid][lid], MPI_BUFF_SIZE, MPI_DOUBLE, info->recvGhostIds[pid][0], bid, MPI_COMM_WORLD, &status); *\/ */
/*     /\* 		    } *\/ */
/*     /\* 		    else { *\/ */
/*     /\* 			int msg = info->recvScalarBlocks[pid] * MPI_BUFF_SIZE - info->recvGhostIds[pid][1]; *\/ */
/*     /\* 			msg = MPI_BUFF_SIZE - msg; *\/ */
/*     /\* 			/\\* MPI_Irecv (&info->parallel.srbuf[pid][lid], msg, MPI_DOUBLE, info->parallel.recvGhostIds[pid][0], bid, MPI_COMM_WORLD, &request); *\\/ *\/ */
/*     /\* 			MPI_Recv (&info->srbuf[pid][lid], MPI_BUFF_SIZE, MPI_DOUBLE, info->recvGhostIds[pid][0], bid, MPI_COMM_WORLD, &status); *\/ */
/*     /\* 		    } *\/ */

/*     /\* 		} *\/ */

/*     /\* 	    } *\/ */


/*     /\* 	    MPI_Barrier(MPI_COMM_WORLD);	     *\/ */
    
/*     /\* 	    /\\* // Finish communication between processors *\\/ *\/ */
/*     /\* 	    /\\* MPI_Wait(&request, &status); *\\/ *\/ */
    

    
/*     /\* 	    // Copy data from buffer *\/ */
    
/*     /\* 	    // Move over send ghosts *\/ */
/*     /\* 	    for( pid = 0 ; pid < info->nRecvGhosts ; pid++ ) { *\/ */
	    
/*     /\* 		unsigned int i; *\/ */
/*     /\* 		for( i = 0 ; i < info->recvGhostIds[pid][1] ; i++ ) { *\/ */
		
/*     /\* 		    // Copy data *\/ */
/*     /\* 		    fld[ info->nlocal + info->recvGhostIds[pid][i+2] ][k] = info->srbuf[pid][i]; *\/ */
		
/*     /\* 		} *\/ */
	    

/*     /\* 	    } *\/ */
   

/*     /\* 	} *\/ */

/*     /\* 	MPI_Barrier(MPI_COMM_WORLD); *\/ */


/*     /\* } *\/ */
    
/* } */




/* // Blocking version */

/* void syncPdfField( struct solverInfo* info, double** fld, int sz ){ */

/*     unsigned int i, j, k, pid; */
    
/*     MPI_Barrier(MPI_COMM_WORLD); */

/*     // Allocate buffers */
/*     double sendBuff[MPI_BUFF_SIZE]; */
/*     double recvBuff[MPI_BUFF_SIZE]; */

    
    
/*     // Send information. Divide by blocks */

/*     for( k = 0 ; k < sz ; k++ ) { */

	
/* 	// Move over send ghosts */
/* 	for( i = 0 ; i < info->parallel.nSendGhosts ; i++ ) { */

/* 	    // Number of blocks */
/* 	    const int buffBlocks = (int)floor( info->parallel.sendGhostIds[i][1] / MPI_BUFF_SIZE ) + 1; */
	
/* 	    unsigned int bid; */
/* 	    for( bid = 0 ; bid < buffBlocks ; bid++ ) { */
	
/* 	    	// Block positions in sendGhostIds */
/* 	    	unsigned int min, max; */
/* 	    	min = MPI_BUFF_SIZE * bid; */
/* 	    	max = MPI_BUFF_SIZE * (bid + 1); */

/* 	    	if(max > info->parallel.sendGhostIds[i][1] ) { max = info->parallel.sendGhostIds[i][1]; } */

	    
/* 	    	// Move over blocks */
/* 	    	unsigned int m = 0; */
/* 	    	for( j = min ; j < max ; j++ ) { */
	    
/* 	    	    sendBuff[m] = fld[ info->parallel.sendGhostIds[i][j+2] ][k]; */
/* 	    	    m++; */

/* 	    	} */

/* 	    	// Send data */
/* 	    	MPI_Send (sendBuff, MPI_BUFF_SIZE, MPI_DOUBLE, info->parallel.sendGhostIds[i][0], (bid + 1) * (k+1), MPI_COMM_WORLD); */

/* 	    } */

/* 	} */
	
	
/*     } */


/*     /\* MPI_Barrier(MPI_COMM_WORLD); *\/ */

    
/*     // Receive information. Divide by blocks */

/*     for( k = 0 ; k < sz ; k++ ) { */

/*     	// Move over recv ghosts */
/*     	for( i = 0 ; i < info->parallel.nRecvGhosts ; i++ ) { */

/*     	    // Number of blocks */
/*     	    const int buffBlocks = (int)floor( info->parallel.sendGhostIds[i][1] / MPI_BUFF_SIZE ) + 1; */
	
/*     	    unsigned int bid; */
/*     	    for( bid = 0 ; bid < buffBlocks ; bid++ ) { */

/*     		// Block positions in recvGhostIds */
/*     		unsigned int min, max; */
/*     		min = MPI_BUFF_SIZE * bid; */
/*     		max = MPI_BUFF_SIZE * (bid + 1); */

/*     		if(max > info->parallel.recvGhostIds[i][1] ) { max = info->parallel.recvGhostIds[i][1]; } */

/*     		// Receive data */
/*     		MPI_Status status; */
/*     		MPI_Recv (recvBuff, MPI_BUFF_SIZE, MPI_DOUBLE, info->parallel.recvGhostIds[i][0], (bid + 1) * (k+1), MPI_COMM_WORLD, &status); */


/*     		// Update field */
/*     		unsigned int m = 0; */
/*     		for( j = min ; j < max ; j++ ) { */

/*     		    fld[ info->lattice.nlocal + info->parallel.recvGhostIds[i][j+2] ][k] = recvBuff[m]; */
/*     		    m++; */

/*     		} */

	    
/*     	    } */
	    
/*     	} */


	
/*     } */
    

/*     MPI_Barrier(MPI_COMM_WORLD); */


    
/* } */
