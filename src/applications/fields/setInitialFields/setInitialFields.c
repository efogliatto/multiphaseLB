/*

  setInitialFields

  Set initial fields using functions, and write in vtk format

 */


#include <dictIO.h>
#include <io.h>
#include <latticeModel.h>
#include <basic.h>


void uniformScalarField( latticeMesh* mesh, double** field, char* fname );

void randomScalarField( latticeMesh* mesh, double** field, char* fname );

void boxBoundedScalarField( latticeMesh* mesh, double** field, char* fname );

void sphereBoundedScalarField( latticeMesh* mesh, double** field, char* fname );

void fixedGradientScalarField( latticeMesh* mesh, double** field, char* fname );
    

int main(int argc, char** argv) {


    
 
    printf("\n  SET DISTRIBUTED FIELDS\n\n");


    
    // Total number of processes

    double dn = 4;

    unsigned int np = 4;
    
    if(  lookUpScalarEntry("properties/parallel","numProc", 4, &dn)  )
    	np = (uint)dn;


    
    

    // Read fields type from file

    vtkInfo vtk = readVTKInfo();

    unsigned int status = 0;


    

    
    // ******************************************************************** //
    //                             Processors                               //
    // ******************************************************************** //



    // Move over processors

    uint pid;
    
    for( pid = 0 ; pid < np ; pid++ ) {


	
    	// Read lattice for each processor

    	latticeMesh mesh = readLatticeMesh(pid);

    	mesh.time.start = 0;

    	mesh.time.current = 0;


    	writeLatticeMesh( &mesh );
	

    	// Write mesh in VTK file
	
    	writeMeshToVTK( &mesh, &vtk );
	

	
    	// Move over scalar fields

    	uint fid;
	
	

    	for( fid = 0 ; fid < vtk.nscalar ; fid++ ) {

	    
    	    double* field;

    	    char* entry;

	    char* itype;
	    
	    
    	    // Internal field type

    	    if( vstring(&entry, "%s/internalField/type", vtk.scalarFields[fid])  ) {
	    
    		status = lookUpStringEntry("start/initialFields", entry, &itype, "uniform");

    	    }

    	    if(status) {}

	    
	   		    

    	    // Uniform distribution
	    
    	    if( strcmp(itype,"uniform") == 0 ) {

    		uniformScalarField( &mesh, &field, vtk.scalarFields[fid] );

    	    }


    	    else {


    		// Random distribution
		
    	    	if( strcmp(itype,"random") == 0 ) {

    		    randomScalarField( &mesh, &field, vtk.scalarFields[fid] );

    	    	}


    	    	else {


    		    // Box bounded
		
    		    if( strcmp(itype,"box") == 0 ) {

    			boxBoundedScalarField( &mesh, &field, vtk.scalarFields[fid] );

    		    }


    		    else {

			
    			// Sphere bounded
		
    			if( strcmp(itype,"sphere") == 0 ) {

    			    sphereBoundedScalarField( &mesh, &field, vtk.scalarFields[fid] );

    			}


    			else {


    			    // fixedGradient
		
    			    if( strcmp(itype,"fixedGradient") == 0 ) {

    				fixedGradientScalarField( &mesh, &field, vtk.scalarFields[fid] );

    			    }
			    
    			    else {

    				errorMsg("Unrecognized type");

    			    }


    			}


    		    }


    	    	}

    	    }

	    
		
		
    	    // Write field
    	    writeScalarToVTK( vtk.scalarFields[fid], field, &mesh );


    	    free(field);

	    free(entry);

	    free(itype);

	    
    	}
	



	

    	// Move over vector fields

    	for( fid = 0 ; fid < vtk.nvector ; fid++ ) {


    	    double** field = matrixDoubleAlloc(  mesh.mesh.nPoints, 3, 0);

    	    double* fval;

    	    char* itype;

    	    char* entry;

    	    unsigned int nn;
	    
	    
    	    // Internal field type
	    
    	    if(  vstring(&entry, "%s/internalField/type", vtk.vectorFields[fid] )  )
    		status = lookUpStringEntry("start/initialFields", entry, &itype, "");
    
	   		    

    	    // Uniform distribution
	    
    	    if( strcmp(itype,"uniform") == 0 ) {

    	    	if(  vstring(&entry, "%s/internalField/value", vtk.vectorFields[fid] )  )
    	    	    status = lookUpVectorEntry("start/initialFields", entry, &fval, &nn);
		

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


	    /* free(entry); */

	    /* free(itype); */

	    /* free(fval); */


    	}


	


    	// Move over pdf fields

    	for( fid = 0 ; fid < vtk.npdf ; fid++ ) {


    	    double** field = matrixDoubleAlloc(  mesh.mesh.nPoints, mesh.mesh.Q, 0 );

    	    double* fval;

    	    char* itype;

    	    char* entry;

    	    unsigned int nn;

		
    	    // Internal field type
	    
    	    if(  vstring(&entry, "%s/internalField/type", vtk.pdfFields[fid] )  )
    		status = lookUpStringEntry("start/initialFields", entry, &itype, "uniform");
    
	   		    

    	    // Uniform distribution
	    
    	    if( strcmp(itype,"uniform") == 0 ) {

    	    	if(  vstring(&entry, "%s/internalField/value", vtk.pdfFields[fid] ) )
    	    	    status = lookUpVectorEntry("start/initialFields", entry, &fval, &nn);
		
		
    	    	uint ii,jj;

    	    	for( ii = 0 ; ii < mesh.mesh.nPoints ; ii++ ) {

    	    	    for( jj = 0 ; jj < mesh.mesh.Q ; jj++ ) {

    	    		field[ii][jj] = fval[jj];

    	    	    }

    	    	}


    	    }

	    

    	    // Write field
    	    writePdfToVTK( vtk.pdfFields[fid], field, &mesh );


    	    /* // Deallocate memory */
	    
    	    /* { */

    	    /* 	uint jj; */

    	    /* 	for( jj = 0 ; jj < mesh.mesh.nPoints ; jj++ ) { */

    	    /* 	    free( field[jj] ); */

    	    /* 	} */

    	    /* 	free(field); */
		
    	    /* } */


	    /* free(entry); */

	    /* free(itype); */

	    /* free(fval); */
	    

    	}
	




	

    	// Write extra terms to vtk file
    	writeVTKExtra( &mesh, &vtk );
	
	

    }



    // Write Main pvd
    writeMainPvd();

    
    
    return 0;

}
