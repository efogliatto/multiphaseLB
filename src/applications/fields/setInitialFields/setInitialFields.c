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


int main(int argc, char** argv) {


    
 
    printf("\n  SET DISTRIBUTED FIELDS\n\n");



    
    // Total number of processes

    uint np = (uint)lookUpDoubleEntry("properties/parallel","numProc",4);

    
    

    // Read fields type from file

    struct vtkInfo vtk;

    unsigned int status;

	
    status = lookUpEntry( "start/initialFields", "scalarFields", vtk.scalarFields, &vtk.nscalar);

    if( !status ) { vtk.nscalar = 0; }

    
    status = lookUpEntry( "start/initialFields", "vectorFields", vtk.vectorFields, &vtk.nvector);

    if( !status ) { vtk.nvector = 0; }
    

    status = lookUpEntry( "start/initialFields", "pdfFields", vtk.pdfFields, &vtk.npdf);

    if( !status ) { vtk.npdf = 0; }



    

    
    // ******************************************************************** //
    //                             Processors                               //
    // ******************************************************************** //



    // Move over processors

    uint pid;

   
    
    for( pid = 0 ; pid < np ; pid++ ) {


	
    	// Read lattice for each processor

    	struct latticeMesh mesh = readLatticeMesh(pid);

    	mesh.time.start = 0;

    	mesh.time.current = 0;

	

    	// Write mesh in VTK file
	
    	writeMeshToVTK( &mesh, &vtk );
	

	
    	// Move over scalar fields

    	uint fid;

	char itype[100];
	
	char fname[100];
	

    	for( fid = 0 ; fid < vtk.nscalar ; fid++ ) {

	    
	    double* field;
	    
	    double fval;

    
	    
    	    // Internal field type
	   
    	    sprintf(fname, "%s/internalField/type", vtk.scalarFields[fid] );
	    
	    status = lookUpString("start/initialFields", fname, itype);

	    
	   		    

    	    // Uniform distribution
	    
    	    if( strcmp(itype,"uniform") == 0 ) {


	    	field = (double*)malloc( mesh.mesh.nPoints * sizeof(double) );
		
		
    	    	sprintf(fname, "%s/internalField/value", vtk.scalarFields[fid] );

	    	status = lookUpDouble("start/initialFields", fname, &fval, 0);


	    	uint ii;

	    	for( ii = 0 ; ii < mesh.mesh.nPoints ; ii++ ) {

	    	    field[ii] = fval;

	    	}


    	    }


	    else {


	    	if( strcmp(itype,"random") == 0 ) {

		    
	    	    field = (double*)malloc( mesh.mesh.nPoints * sizeof(double) );

	    	    sprintf(fname, "%s/internalField/value", vtk.scalarFields[fid] );

	    	    status = lookUpDouble("start/initialFields", fname, &fval, 0);
		    

	    	    double pert;

	    	    sprintf(fname, "%s/internalField/perturbation", vtk.scalarFields[fid] );

	    	    status = lookUpDouble("start/initialFields", fname, &pert, 1);


		    
	    	    // Generate random numbers

	    	    srand( time(NULL) );

	    	    uint ii;

	    	    for( ii = 0 ; ii < mesh.mesh.nPoints ; ii++ ) {

	    		// Random number between 0 and 1

	    		double r = (double)rand() / (double)RAND_MAX;

	    		r = (1.0 - pert/100) + r * ( (1.0 + pert/100) - (1.0 - pert/100) );
			
	    		field[ii] = fval * r;

	    	    }


	    	}


	    	else {

	    	    printf("\n   [ERROR]  Unrecognized type %s\n\n", itype);

	    	    exit(1);

	    	}

	    }

		
		
	    // Write field
	    writeScalarToVTK( vtk.scalarFields[fid], field, &mesh );


	    free(field);


	    
    	}
	



	

    	// Move over vector fields

    	for( fid = 0 ; fid < vtk.nvector ; fid++ ) {


    	    double** field = matrixDoubleAlloc(  mesh.mesh.nPoints, 3, 0);

	    double fval[3];

	    char itype[100];
	    
	    
    	    // Internal field type
	    
    	    sprintf(fname, "%s/internalField/type", vtk.vectorFields[fid] );
	    
	    status = lookUpString("start/initialFields", fname, itype);
    
	   		    

    	    // Uniform distribution
	    
    	    if( strcmp(itype,"uniform") == 0 ) {

    	    	sprintf(fname, "%s/internalField/value", vtk.vectorFields[fid] );

		status = lookUpVector("start/initialFields", fname, fval, 3);
		

		uint ii,jj;

		for( ii = 0 ; ii < mesh.mesh.nPoints ; ii++ ) {

		    for( jj = 0 ; jj < 3 ; jj++ ) {

			field[ii][jj] = fval[jj];

		    }

		}


    	    }
	    


    	    // Write field
    	    writeVectorToVTK( vtk.vectorFields[fid], field, &mesh );


	    // Deallocate memory
	    
	    {

		uint jj;

		for( jj = 0 ; jj < mesh.mesh.nPoints ; jj++ ) {

		    free( field[jj] );

		}

		free(field);
		
	    }


    	}


	


    	// Move over pdf fields

    	for( fid = 0 ; fid < vtk.npdf ; fid++ ) {


    	    double** field = matrixDoubleAlloc(  mesh.mesh.nPoints, mesh.mesh.Q, 0);

	    double fval[20];

	    char itype[100];
	    
    	    // Internal field type
	    
    	    sprintf(fname, "%s/internalField/type", vtk.pdfFields[fid] );
	    
	    status = lookUpString("start/initialFields", fname, itype);
    
	   		    

    	    // Uniform distribution
	    
    	    if( strcmp(itype,"uniform") == 0 ) {

    	    	sprintf(fname, "%s/internalField/value", vtk.pdfFields[fid] );

		status = lookUpVector("start/initialFields", fname, fval, mesh.mesh.Q);
		

		uint ii,jj;

		for( ii = 0 ; ii < mesh.mesh.nPoints ; ii++ ) {

		    for( jj = 0 ; jj < mesh.mesh.Q ; jj++ ) {

			field[ii][jj] = fval[jj];

		    }

		}


    	    }
	    


    	    // Write field
    	    writePdfToVTK( vtk.pdfFields[fid], field, &mesh );


	    // Deallocate memory
	    
	    {

		uint jj;

		for( jj = 0 ; jj < mesh.mesh.nPoints ; jj++ ) {

		    free( field[jj] );

		}

		free(field);
		
	    }
	    

    	}
	




	

    	// Write extra terms to vtk file
    	writeVTKExtra( &mesh, &vtk );
	
	

    }



    // Write Main pvd
    writeMainPvd();

    
    
    return 0;

}
