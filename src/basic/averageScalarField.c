#include <averageScalarField.h>


double averageScalarField( latticeMesh* mesh, double* fld ) {


    double avg = 0;


    if (mesh->EOS.rho_0 <= 0) {

	avg = 0;

    }



    else {
    

	// Sum local nodes locally

	double localSum = 0;

	int i = 0;


	for( i = 0 ; i < mesh->parallel.nlocal ; i++ ) {

	    localSum += fld[i];

	}
    


	// Apply collective reduction

	double globalSum = 0;

	int nelem = 0;

	int nlocal = mesh->parallel.nlocal;
    
	if( mesh->parallel.worldSize > 1 ) {

	    MPI_Allreduce(&localSum, &globalSum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	    MPI_Allreduce(&nlocal, &nelem, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);	

	}

	else {

	    globalSum = localSum;

	    nelem = mesh->parallel.nlocal;

	}



	avg = globalSum / nelem;

    }    

    return avg;
	
}
