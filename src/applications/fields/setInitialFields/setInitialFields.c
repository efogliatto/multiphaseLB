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

    
    // List available fields in start folder
    struct vtkInfo vtk;
 
    vtk.nscalar = 0;

    vtk.nvector = 0;

    vtk.npdf = 0;

    
    
    {
	DIR           *d;
	
	struct dirent *dir;
	
	d = opendir("start");
	
	if (d)	{
	    
	    while ((dir = readdir(d)) != NULL)  {

		if(   ( strcmp(dir->d_name,"rho") == 0 )  ||  ( strcmp(dir->d_name,"p")   == 0 )  ||  ( strcmp(dir->d_name,"T")   == 0 )   ) {

		    sprintf(vtk.scalarFields[vtk.nscalar],"%s",dir->d_name);
		    
		    vtk.nscalar++;
		    
		}

		else {

		    if(   ( strcmp(dir->d_name,"U") == 0 )   ) {

			sprintf(vtk.vectorFields[vtk.nvector],"%s",dir->d_name);
		    
			vtk.nvector++;
		    
		    }

		    else {

			if(   ( strcmp(dir->d_name,"f") == 0 )  ||  ( strcmp(dir->d_name,"g")   == 0 )  ) {

			    sprintf(vtk.pdfFields[vtk.npdf],"%s",dir->d_name);
		    
			    vtk.npdf++;
		    
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

	mesh.time.start = 0;

	mesh.time.current = 0;


	// Write mesh in VTK file
	writeMeshToVTK( &mesh, &vtk );
	

	

	// Move over scalar fields

	uint fid;

	for( fid = 0 ; fid < vtk.nscalar ; fid++ ) {


	    // Scalar fields: rho, p, T
	    if(   ( strcmp( vtk.scalarFields[fid], "rho" ) == 0 )   ||   ( strcmp( vtk.scalarFields[fid], "p" ) == 0 )   ||  ( strcmp( vtk.scalarFields[fid], "T" ) == 0 )   ) {


		// Resize field array
		double* field = (double*)malloc( mesh.mesh.nPoints * sizeof(double) );

		// Read type and use function
		char intField[100];
		char fn[100];

		// Field file name
		sprintf(fn,"start/%s", vtk.scalarFields[fid]);

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
		if( strcmp(intField, "random") == 0 ) {

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




		// Write field
		writeScalarToVTK( vtk.scalarFields[fid], field, &mesh );
		
		

	    }


	}
	




	// Move over vector fields

	for( fid = 0 ; fid < vtk.nvector ; fid++ ) {

	    if(   ( strcmp( vtk.vectorFields[fid], "U" ) == 0 )   ) {

	    	double** field = matrixDoubleAlloc(  mesh.mesh.nPoints, 3, 0);

		// Write field
		writeVectorToVTK( vtk.vectorFields[fid], field, &mesh );

	    }

	}




	// Move over pdf fields

	for( fid = 0 ; fid < vtk.npdf ; fid++ ) {

	    if(   ( strcmp( vtk.pdfFields[fid], "f" ) == 0 )   ||   ( strcmp( vtk.pdfFields[fid], "g" ) == 0 )  ) {

	    	double** field = matrixDoubleAlloc(  mesh.mesh.nPoints, mesh.mesh.Q, 0);
		
		// Write field
		writePdfToVTK( vtk.pdfFields[fid], field, &mesh );

	    }

	}








	// Write extra terms to vtk file
	writeVTKExtra( &mesh, &vtk );
	
	

    }



    // Write Main pvd
    writeMainPvd();

    
    
    return 0;

}