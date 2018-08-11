#include <stdlib.h>
#include <stdio.h>
#include <recvPdfField.h>
#include <math.h>


void recvPdfField( latticeMesh* mesh, lbeField* field ) {


    if( mesh->parallel.worldSize > 1 ) {

	
	// Wait for everyone

	MPI_Waitall(field->nreq, field->request, field->status);


	

	// Copy new data back to ghost nodes

	uint pid;
	
	for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {

	    
	    unsigned int i, k, id;

	    for( i = 0 ; i < mesh->parallel.nrg[pid] ; i++) {

		for( k = 0 ; k < mesh->mesh.Q ; k++ ) {


		    // Position in sbuf

		    id = i*mesh->mesh.Q + k;

		    
		    // Copy field info
		    
		    field->value[ mesh->parallel.recvGhosts[pid][i] ][ k ] = field->rbuf[pid][id];
		    

		}

	    }		

	    
	}	


    }
	
}
