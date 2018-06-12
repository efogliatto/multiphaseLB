#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <syncScalarField.h>


void syncScalarField( latticeMesh* mesh, scalar* fld ) {


    if( mesh->parallel.worldSize > 1 ) {

	
    	MPI_Barrier(MPI_COMM_WORLD);

	

	// Move over send ghosts. Copy data to buffer

	unsigned int pid;

	for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {


	    unsigned int i;

	    for( i = 0 ; i < mesh->parallel.nsg[pid] ; i++) {

		
		// Copy field info
		    
		mesh->parallel.vsbuf[pid][i] = fld[ mesh->parallel.sendGhosts[pid][i] ];


	    }
	  

	}




    	// Send information
    	
    	MPI_Status status[100];

	MPI_Request request[100];

	int nreq = 0;

	
	// Move over send ghosts. Send data

	for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {

	    if( mesh->parallel.nsg[pid] > 0 ) {

		#ifdef DP
		
		MPI_Isend (&mesh->parallel.vsbuf[pid][0], mesh->parallel.nsg[pid], MPI_DOUBLE, pid, mesh->parallel.pid, MPI_COMM_WORLD, &request[nreq]);

		#elif SP

		MPI_Isend (&mesh->parallel.vsbuf[pid][0], mesh->parallel.nsg[pid], MPI_FLOAT, pid, mesh->parallel.pid, MPI_COMM_WORLD, &request[nreq]);

		#endif

		nreq++;

	    }
	}



	// Move over recv ghosts. Receive data

	for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {

	    if( mesh->parallel.nrg[pid] > 0 ) {

		#ifdef DP
		
		MPI_Irecv (mesh->parallel.vrbuf[pid], mesh->parallel.nrg[pid], MPI_DOUBLE, pid, pid, MPI_COMM_WORLD, &request[nreq]);

		#elif SP

		MPI_Irecv (mesh->parallel.vrbuf[pid], mesh->parallel.nrg[pid], MPI_FLOAT, pid, pid, MPI_COMM_WORLD, &request[nreq]);

		#endif

		nreq++;

	    }
	}


	
	// Wait for everyone

	MPI_Waitall(nreq, request, status);







	

	// Copy new data back to ghost nodes

	for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {

	    
	    unsigned int i;

	    for( i = 0 ; i < mesh->parallel.nrg[pid] ; i++) {

		    
		    // Copy field info
		    
		    fld[ mesh->parallel.recvGhosts[pid][i] ] = mesh->parallel.vrbuf[pid][i];

		    
	    }		

	    
	}	
	
	

	// Wait for everyone
	
	MPI_Barrier(MPI_COMM_WORLD);

    }
	
}
