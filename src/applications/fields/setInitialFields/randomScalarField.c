#include <dictIO.h>
#include <latticeMesh.h>
#include <stdlib.h>
#include <stdio.h>
#include <basic.h>


void randomScalarField( latticeMesh* mesh, double** field, char* fname ) {


    // Allocate memory
    
    *field = (double*)malloc( mesh->mesh.nPoints * sizeof(double) );


    
    // Look for values

    char* aux;

    double fval = 0;

    unsigned int status;
    
    
    if(  vstring(&aux, "%s/internalField/value", fname)  )
	status = lookUpScalarEntry("start/initialFields", aux, 0, &fval);

    if (status) {}



    double pert = 0;

    if(  vstring(&aux, "%s/internalField/perturbation", fname )  )
	status = lookUpScalarEntry("start/initialFields", aux, 1, &pert);
    


    srand( time(NULL) );    
    
    uint ii;

    for( ii = 0 ; ii < mesh->mesh.nPoints ; ii++ ) {

	
	// Random number between 0 and 1

	double r = (double)rand() / (double)RAND_MAX;

	r = (1.0 - pert/100) + r * ( (1.0 + pert/100) - (1.0 - pert/100) );
			
	field[0][ii] = fval * r;
	

    }
    


    free(aux);
    
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
