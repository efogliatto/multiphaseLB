/*

  setInitialFields

  Set initial fields using functions, and write in vtk format

 */


#include <dictIO.h>
#include <io.h>
#include <latticeModel.h>
#include <basic.h>


void uniformScalarField( latticeMesh* mesh, scalar** field, char* fname );

void randomScalarField( latticeMesh* mesh, scalar** field, char* fname );

void boxBoundedScalarField( latticeMesh* mesh, scalar** field, char* fname );

void sphereBoundedScalarField( latticeMesh* mesh, scalar** field, char* fname );

void fixedGradientScalarField( latticeMesh* mesh, scalar** field, char* fname );
    

int main(int argc, char** argv) {


    
 
    printf("\n  SET DISTRIBUTED FIELDS\n\n");


    
    // Total number of processes

    scalar dn = 4;

    uint np = 4;
    
    if(  lookUpScalarEntry("properties/parallel","numProc", 4, &dn)  )
    	np = (uint)dn;


    
    

    // Read fields type from file

    vtkInfo vtk = readVTKInfo();

    uint status = 0;



    // Time info

    dataFormat tinfo = readDataFormat();
    


    
    

    
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

	if(tinfo == pvtu) {
	
	    writeMeshToVTK( &mesh, &vtk );

	}
	

	
    	// Move over scalar fields

    	uint fid;
	
	

    	for( fid = 0 ; fid < vtk.nscalar ; fid++ ) {

	    
    	    scalar* field;

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
	    
    	    writeScalarField( vtk.scalarFields[fid], field, &mesh );


    	    free(field);

	    free(entry);

	    free(itype);

	    
    	}
	



	

    	// Move over vector fields

    	for( fid = 0 ; fid < vtk.nvector ; fid++ ) {


    	    scalar** field = matrixDoubleAlloc(  mesh.mesh.nPoints, 3, 0);

    	    scalar* fval;

    	    char* itype;

    	    char* entry;

    	    uint nn;
	    
	    
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

    	    writeVectorField( vtk.vectorFields[fid], field, &mesh, 3 );


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


    	    scalar** field = matrixDoubleAlloc(  mesh.mesh.nPoints, mesh.mesh.Q, 0 );

    	    scalar* fval;

    	    char* itype;

    	    char* entry;

    	    uint nn;

		
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
    	    writeVectorField( vtk.pdfFields[fid], field, &mesh, mesh.lattice.Q );


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

	if(tinfo == pvtu) {
	    
	    writePvtuExtra( &mesh, &vtk );

	}
	

    }



    // Write Main pvd

    if(tinfo == pvtu) {
		
    	writeMainPvd();

    }
    
    
    return 0;

}
