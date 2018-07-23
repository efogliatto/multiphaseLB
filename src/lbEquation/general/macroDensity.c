#include <macroDensity.h>
#include <basic.h>
#include <lbEquation.h>



void macroDensity( latticeMesh* mesh, macroFields* mfields, lbeField* field ) {


    if (field->update != 0) {


	unsigned int pid;
	
	MPI_Status status[100];

	MPI_Request request[100];

	int nreq = 0;

	

	// First do non blocking communications

	if( mesh->parallel.worldSize > 1 ) {

	
	    MPI_Barrier(MPI_COMM_WORLD);

	
	    // Move over send ghosts. Copy data to buffer

	    for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {


		unsigned int i, k, id;

		for( i = 0 ; i < mesh->parallel.nsg[pid] ; i++) {

		    for( k = 0 ; k < mesh->mesh.Q ; k++ ) {


			// Position in sbuf

			id = i*mesh->mesh.Q + k;

		    
			// Copy field info
		    
			mesh->parallel.sbuf[pid][id] = field->value[ mesh->parallel.sendGhosts[pid][i] ][ k ];
		    

		    }

		}
	  

	    }



	
	    // Send information    	

	
	    // Move over send ghosts. Send data

	    for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {

		if( mesh->parallel.nsg[pid] > 0 ) {

                    #ifdef DP
		
		    MPI_Isend (&mesh->parallel.sbuf[pid][0], mesh->parallel.nsg[pid] * mesh->mesh.Q, MPI_DOUBLE, pid, mesh->parallel.pid, MPI_COMM_WORLD, &request[nreq]);

                    #elif SP

		    MPI_Isend (&mesh->parallel.sbuf[pid][0], mesh->parallel.nsg[pid] * mesh->mesh.Q, MPI_FLOAT, pid, mesh->parallel.pid, MPI_COMM_WORLD, &request[nreq]);

                    #endif

		    nreq++;

		}
	    }



	    // Move over recv ghosts. Receive data

	    for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {

		if( mesh->parallel.nrg[pid] > 0 ) {

                    #ifdef DP
		
		    MPI_Irecv (mesh->parallel.rbuf[pid], mesh->parallel.nrg[pid] * mesh->mesh.Q, MPI_DOUBLE, pid, pid, MPI_COMM_WORLD, &request[nreq]);

                    #elif SP

		    MPI_Irecv (mesh->parallel.rbuf[pid], mesh->parallel.nrg[pid] * mesh->mesh.Q, MPI_DOUBLE, pid, pid, MPI_COMM_WORLD, &request[nreq]);

                    #endif

		    nreq++;

		}
	    }


	}









	
	
	// Compute density according to field.colId
    
	uint id;
    
    
	// Apply collision model
	switch(field->model) {

	
	// Li MRT Model
	case liMRT:

	    for( id = 0 ; id < mesh->parallel.nlocal ; id++) {
	    
		mfields->rho[id] = liMRTDensity( mesh, field->value[id] );
	    
	    }
	
	    break;


	// My MRT Model
	case myMRT:

	    errorMsg("Density update not suitable for myMRTModel");
	
	    break;
	


	// xU MRT Model
	case xuMRT:

	    for( id = 0 ; id < mesh->parallel.nlocal ; id++) {
	    
		mfields->rho[id] = xuMRTDensity( mesh, field->value[id] );
	    
	    }
	
	    break;


	    
	
	default:

	    errorMsg("Density update not available");

	    break;	
	
	}







	if(mesh->parallel.worldSize > 1) {
	    

	    // Wait for everyone

	    MPI_Waitall(nreq, request, status);	


	    // Copy new data back to ghost nodes

	    for( pid = 0 ; pid < mesh->parallel.worldSize ; pid++ ) {

	    
		unsigned int i, k, id;

		for( i = 0 ; i < mesh->parallel.nrg[pid] ; i++) {

		    for( k = 0 ; k < mesh->mesh.Q ; k++ ) {


			// Position in sbuf

			id = i*mesh->mesh.Q + k;

		    
			// Copy field info
		    
			field->value[ mesh->parallel.recvGhosts[pid][i] ][ k ] = mesh->parallel.rbuf[pid][id];
		    

		    }

		}		

	    
	    }



            // Apply collision model
	    switch(field->model) {

	
		// Li MRT Model
	    case liMRT:

		for( id = mesh->parallel.nlocal ; id < mesh->mesh.nPoints ; id++) {
	    
		    mfields->rho[id] = liMRTDensity( mesh, field->value[id] );
	    
		}
	
		break;


		// My MRT Model
	    case myMRT:

		errorMsg("Density update not suitable for myMRTModel");
	
		break;
	


		// xU MRT Model
	    case xuMRT:

		for( id = mesh->parallel.nlocal ; id < mesh->mesh.nPoints ; id++) {
	    
		    mfields->rho[id] = xuMRTDensity( mesh, field->value[id] );
	    
		}
	
		break;


	    
	
	    default:

		errorMsg("Density update not available");

		break;
	
	    }	
	    


	}
	





    	

	
    }









    
}









/* // Base Version */

/* void macroDensity( latticeMesh* mesh, macroFields* mfields, lbeField* field ) { */


/*     if (field->update != 0) { */

	
/* 	// Compute density according to field.colId */
    
/* 	uint id; */
    
    
/* 	// Apply collision model */
/* 	switch(field->model) { */

	
/* 	// Li MRT Model */
/* 	case liMRT: */

/* 	    for( id = 0 ; id < mesh->mesh.nPoints ; id++) { */
	    
/* 		mfields->rho[id] = liMRTDensity( mesh, field->value[id] ); */
	    
/* 	    } */
	
/* 	    break; */


/* 	// My MRT Model */
/* 	case myMRT: */

/* 	    errorMsg("Density update not suitable for myMRTModel"); */
	
/* 	    break; */
	


/* 	// xU MRT Model */
/* 	case xuMRT: */

/* 	    for( id = 0 ; id < mesh->mesh.nPoints ; id++) { */
	    
/* 		mfields->rho[id] = xuMRTDensity( mesh, field->value[id] ); */
	    
/* 	    } */
	
/* 	    break; */


	    
	
/* 	default: */

/* 	    errorMsg("Density update not available"); */

/* 	    break;	 */
	
/* 	} */

/*     } */
    
/* } */
