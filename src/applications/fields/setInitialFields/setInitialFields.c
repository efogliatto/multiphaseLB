/*

  setInitialFields

  Set initial fields using functions, and write in vtk format

 */


#include <io.h>
#include <latticeModel.h>
#include <basic.h>
#include <readLatticeMesh.h>
#include <writeLatticeMesh.h>
#include <dirent.h>
#include <time.h>

int main(int argc, char** argv) {


    
 
    printf("\n  SET DISTRIBUTED FIELDS\n\n");



    
    // Total number of processes
    uint np = (uint)lookUpDoubleEntry("properties/parallel","numProc",4);

    
    // List available fields in start folder

    uint nScalarFields = 0;
    char scalarFields[10][100];

    uint nVectorFields = 0;
    char vectorFields[10][100];

    uint nPdfFields = 0;
    char pdfFields[10][100];
    
    
    {
	DIR           *d;
	
	struct dirent *dir;
	
	d = opendir("start");
	
	if (d)	{
	    
	    while ((dir = readdir(d)) != NULL)  {

		if(   ( strcmp(dir->d_name,"rho") == 0 )  ||  ( strcmp(dir->d_name,"p")   == 0 )  ||  ( strcmp(dir->d_name,"T")   == 0 )   ) {

		    sprintf(scalarFields[nScalarFields],"%s",dir->d_name);
		    
		    nScalarFields++;
		    
		}

		else {

		    if(   ( strcmp(dir->d_name,"U") == 0 )   ) {

			sprintf(vectorFields[nVectorFields],"%s",dir->d_name);
		    
			nVectorFields++;
		    
		    }

		    else {

			if(   ( strcmp(dir->d_name,"f") == 0 )  ||  ( strcmp(dir->d_name,"g")   == 0 )  ) {

			    sprintf(pdfFields[nPdfFields],"%s",dir->d_name);
		    
			    nPdfFields++;
		    
			}

		    }

		}
		
	    }

	    closedir(d);
	}



	

	
    }
    
    
    
    // ******************************************************************** //
    //                             Processors                               //
    // ******************************************************************** //



    // Move over processors

    uint pid, i;
    
    for( pid = 0 ; pid < np ; pid++ ) {


	
	// Read lattice for each processor

	struct latticeMesh mesh = readLatticeMesh(pid);

	

	// Move over scalar fields

	uint fid;

	for( fid = 0 ; fid < nScalarFields ; fid++ ) {


	    // Scalar fields: rho, p, T
	    if(   ( strcmp( scalarFields[fid], "rho" ) == 0 )   ||   ( strcmp( scalarFields[fid], "p" ) == 0 )   ||  ( strcmp( scalarFields[fid], "T" ) == 0 )   ) {


		// Resize field array
		double* field = (double*)malloc( mesh.mesh.nPoints * sizeof(double) );

		// Read type and use function
		char intField[100];
		char fn[100];

		// Field file name
		sprintf(fn,"start/%s", scalarFields[fid]);

		// Internal field distribution
		lookUpStringEntry(fn,"internalField", intField);



		
		// Uniform
		if( strcmp(intField, "uniform") == 0 ) {

		    double value = lookUpDoubleEntry(fn, "internalValue", 0);

		    for( i = 0 ; i < mesh.mesh.nPoints ; i++ ) {

			field[i] = value;
		    }

		}


		
		
		// Random
		if( strcmp(intField, "uniform") == 0 ) {

		    double value = lookUpDoubleEntry(fn, "internalValue", 0);

		    double pert = lookUpDoubleEntry(fn, "perturbation", 1);

		    // Generate random numbers
		    srand( time(NULL) );

		    for( i = 0 ; i < mesh.mesh.nPoints ; i++ ) {

			// Random number between 0 and 1
			double r = (double)rand() / (double)RAND_MAX;

			r = (1.0 - pert/100) + r * ( (1.0 + pert/100) - (1.0 - pert/100) );
			
			field[i] = value * r;
			
		    }		    

		}
		
		

	    }


	}
	




	// Move over vector fields

	for( fid = 0 ; fid < nVectorFields ; fid++ ) {

	    if(   ( strcmp( vectorFields[fid], "U" ) == 0 )   ) {

	    	double** field = matrixDoubleAlloc(  mesh.mesh.nPoints, 3, 0);

	    }

	}




	// Move over pdf fields

	for( fid = 0 ; fid < nPdfFields ; fid++ ) {

	    if(   ( strcmp( pdfFields[fid], "f" ) == 0 )   ||   ( strcmp( pdfFields[fid], "g" ) == 0 )  ) {

	    	double** field = matrixDoubleAlloc(  mesh.mesh.nPoints, mesh.mesh.Q, 0);

	    }

	}



	
	

    }


    
    
    return 0;

}
