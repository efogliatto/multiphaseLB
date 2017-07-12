#include <io.h>
#include <latticeMesh.h>
#include <stdlib.h>
#include <stdio.h>

void randomScalarField( struct latticeMesh* mesh, double** field, char* fname ) {


    // Allocate memory
    
    *field = (double*)malloc( mesh->mesh.nPoints * sizeof(double) );


    
    // Look for values

    char aux[100];

    double fval = 0;
    
    sprintf(aux, "%s/internalField/value", fname);

    unsigned int status = lookUpDouble("start/initialFields", aux, &fval, 0);

    if (status) {}



    double pert = 0;

    sprintf(aux, "%s/internalField/perturbation", fname );

    status = lookUpDouble("start/initialFields", aux, &pert, 1);
    


    srand( time(NULL) );    
    
    uint ii;

    for( ii = 0 ; ii < mesh->mesh.nPoints ; ii++ ) {

	
	// Random number between 0 and 1

	double r = (double)rand() / (double)RAND_MAX;

	r = (1.0 - pert/100) + r * ( (1.0 + pert/100) - (1.0 - pert/100) );
			
	field[0][ii] = fval * r;
	

    }
    


}




/* field = (double*)malloc( mesh.mesh.nPoints * sizeof(double) ); */

/* sprintf(fname, "%s/internalField/value", vtk.scalarFields[fid] ); */

/* status = lookUpDouble("start/initialFields", fname, &fval, 0); */
		    

/* double pert; */

/* sprintf(fname, "%s/internalField/perturbation", vtk.scalarFields[fid] ); */

/* status = lookUpDouble("start/initialFields", fname, &pert, 1); */


		    
/* // Generate random numbers */

/* srand( time(NULL) ); */

/* uint ii; */

/* for( ii = 0 ; ii < mesh.mesh.nPoints ; ii++ ) { */

/*     // Random number between 0 and 1 */

/*     double r = (double)rand() / (double)RAND_MAX; */

/*     r = (1.0 - pert/100) + r * ( (1.0 + pert/100) - (1.0 - pert/100) ); */
			
/*     field[ii] = fval * r; */

/* } */
