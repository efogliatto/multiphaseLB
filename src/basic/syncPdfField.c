#include <stdlib.h>
#include <stdio.h>
#include <syncPdfField.h>
/* #include <latticeMesh.h> */
/* #include <mpi.h> */
#include <math.h>


void syncPdfField( latticeMesh* mesh, double** fld ) {


    if( mesh->parallel.worldSize > 1 ) {

	
    	MPI_Barrier(MPI_COMM_WORLD);

	
	// Move over send ghosts. Copy data to buffer

	unsigned int pid;

	for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {


	    unsigned int i, k, id;

	    for( i = 0 ; i < mesh->parallel.nsg[pid] ; i++) {

		for( k = 0 ; k < mesh->mesh.Q ; k++ ) {


		    // Position in sbuf

		    id = i*mesh->mesh.Q + k;

		    
		    // Copy field info
		    
		    mesh->parallel.sbuf[pid][id] = fld[ mesh->parallel.sendGhosts[pid][i] ][ k ];
		    

		}

	    }
	  

	}



	
    	// Send information
    	
    	MPI_Status status[100];

	MPI_Request request[100];

	int nreq = 0;

	
	// Move over send ghosts. Send data

	for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {

	    if( mesh->parallel.nsg[pid] > 0 ) {
	    
		MPI_Isend (&mesh->parallel.sbuf[pid][0], mesh->parallel.nsg[pid] * mesh->mesh.Q, MPI_DOUBLE, pid, mesh->parallel.pid, MPI_COMM_WORLD, &request[nreq]);

		nreq++;

	    }
	}



	// Move over recv ghosts. Receive data

	for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {

	    if( mesh->parallel.nrg[pid] > 0 ) {
	    
		MPI_Irecv (mesh->parallel.rbuf[pid], mesh->parallel.nrg[pid] * mesh->mesh.Q, MPI_DOUBLE, pid, pid, MPI_COMM_WORLD, &request[nreq]);

		nreq++;

	    }
	}


	
	// Wait for everyone

	MPI_Waitall(nreq, request, status);




	

        /* // Send information */
    	
	/* MPI_Status status; */

	
        /* // Move over send ghosts. Send data */

	/* for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) { */

	/*     if( mesh->parallel.shared[pid] > 0 ) { */
	    
	/* 	MPI_Send (&mesh->parallel.sbuf[pid][0], mesh->parallel.shared[pid] * mesh->mesh.Q, MPI_DOUBLE, pid, mesh->parallel.pid, MPI_COMM_WORLD); */

	/*     } */
	/* } */



        /* // Wait for everyone */
	
	/* MPI_Barrier(MPI_COMM_WORLD); */

	
        /* // Move over recv ghosts. Receive data */

	/* for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) { */

	/*     if( mesh->parallel.shared[pid] > 0 ) { */
	    
	/* 	MPI_Recv (mesh->parallel.rbuf[pid], mesh->parallel.shared[pid] * mesh->mesh.Q, MPI_DOUBLE, pid, pid, MPI_COMM_WORLD, &status); */

	/*     } */
	/* } */


        /* // Wait for everyone */
	
	/* MPI_Barrier(MPI_COMM_WORLD); */

	


	


	// Copy new data back to ghost nodes

	for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {

	    
	    unsigned int i, k, id;

	    for( i = 0 ; i < mesh->parallel.nrg[pid] ; i++) {

		for( k = 0 ; k < mesh->mesh.Q ; k++ ) {


		    // Position in sbuf

		    id = i*mesh->mesh.Q + k;

		    
		    // Copy field info
		    
		    fld[ mesh->parallel.recvGhosts[pid][i] ][ k ] = mesh->parallel.rbuf[pid][id];
		    

		}

	    }		

	    
	}	
	
	

	// Wait for everyone
	
	MPI_Barrier(MPI_COMM_WORLD);

    }
	
}










/* // Blocking - comm */


/* // Send information */
    	
/* MPI_Status status; */

	
/* // Move over send ghosts. Send data */

/* for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) { */

/*     if( mesh->parallel.shared[pid] > 0 ) { */
	    
/* 	MPI_Send (&mesh->parallel.sbuf[pid][0], mesh->parallel.shared[pid] * mesh->mesh.Q, MPI_DOUBLE, pid, mesh->parallel.pid, MPI_COMM_WORLD); */

/*     } */
/* } */



/* // Wait for everyone */
	
/* MPI_Barrier(MPI_COMM_WORLD); */

	
/* // Move over recv ghosts. Receive data */

/* for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) { */

/*     if( mesh->parallel.shared[pid] > 0 ) { */
	    
/* 	MPI_Recv (mesh->parallel.rbuf[pid], mesh->parallel.shared[pid] * mesh->mesh.Q, MPI_DOUBLE, pid, pid, MPI_COMM_WORLD, &status); */

/*     } */
/* } */


/* // Wait for everyone */
	
/* MPI_Barrier(MPI_COMM_WORLD); */

	
