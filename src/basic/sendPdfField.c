#include <stdlib.h>
#include <stdio.h>
#include <sendPdfField.h>
#include <math.h>


void sendPdfField( latticeMesh* mesh, lbeField* field ) {


    if( mesh->parallel.worldSize > 1 ) {
       

	
	// Move over send ghosts. Copy data to buffer

	unsigned int pid;

	for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {


	    unsigned int i, k, id;

	    for( i = 0 ; i < mesh->parallel.nsg[pid] ; i++) {

		for( k = 0 ; k < mesh->mesh.Q ; k++ ) {


		    // Position in sbuf

		    id = i*mesh->mesh.Q + k;

		    
		    // Copy field info
		    
		    field->sbuf[pid][id] = field->value[ mesh->parallel.sendGhosts[pid][i] ][ k ];
		    

		}

	    }
	  

	}



	
    	// Send information    	

	field->nreq = 0;

	
	// Move over send ghosts. Send data

	for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {

	    if( mesh->parallel.nsg[pid] > 0 ) {

		#ifdef DP
		
		MPI_Isend (&field->sbuf[pid][0], mesh->parallel.nsg[pid] * mesh->mesh.Q, MPI_DOUBLE, pid, mesh->parallel.pid, MPI_COMM_WORLD, &field->request[field->nreq]);

		#elif SP

		MPI_Isend (&field->sbuf[pid][0], mesh->parallel.nsg[pid] * mesh->mesh.Q, MPI_FLOAT, pid, mesh->parallel.pid, MPI_COMM_WORLD, &field->request[field->nreq]);

		#endif

		field->nreq = field->nreq + 1;

	    }
	}



	// Move over recv ghosts. Receive data

	for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {

	    if( mesh->parallel.nrg[pid] > 0 ) {

		#ifdef DP
		
		MPI_Irecv (field->rbuf[pid], mesh->parallel.nrg[pid] * mesh->mesh.Q, MPI_DOUBLE, pid, pid, MPI_COMM_WORLD, &field->request[field->nreq]);

		#elif SP

		MPI_Irecv (field->rbuf[pid], mesh->parallel.nrg[pid] * mesh->mesh.Q, MPI_DOUBLE, pid, pid, MPI_COMM_WORLD, &field->request[field->nreq]);

		#endif

		field->nreq = field->nreq + 1;

	    }
	}


	

    }
	
}
