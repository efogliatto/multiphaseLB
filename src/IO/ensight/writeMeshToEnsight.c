#include <latticeMesh.h>
#include <stdio.h>
#include <stdlib.h>
#include <writeMeshToEnsight.h>
#include <basic.h>
#include <vtkInfo.h>
#include <readVTKInfo.h>
#include <updateCaseFile.h>


void writeMeshToEnsight( latticeMesh* mesh ) {

    FILE *outFile;

    char fileName[100];


   
    // Write Mesh
    
    sprintf(fileName, "lattice.geo");


    // Headers first

    if( mesh->parallel.pid == 0 ) {

	    
	// Open File
	    
	outFile = fopen(fileName, "w");

	testFile(outFile, fileName);
	
	
	// Headers

	fprintf(outFile,"EnSight Model Geometry File\n");
	fprintf(outFile,"EnSight 7.4.1\n");
	fprintf(outFile,"node id assign\n");
	fprintf(outFile,"element id assign\n");
	fprintf(outFile,"extents\n");
	fprintf(outFile," 0.00000e+00 1.00000e+00\n");
	fprintf(outFile," 0.00000e+00 1.00000e+00\n");
	fprintf(outFile," 0.00000e+00 0.00000e+00\n");
	    

	fclose(outFile);

	

	// Create .case file
	
	updateCaseFile( mesh );	

    }



    // Points coordinates

    outFile = fopen(fileName, "a");

    testFile(outFile, fileName);

    fprintf(outFile,"part\n");

    fprintf(outFile,"%10d\n",mesh->parallel.pid+1);

    fprintf(outFile,"Point field\n");

    fprintf(outFile,"coordinates\n");

    fprintf(outFile,"%10d\n",mesh->mesh.nPoints);


    
    uint i,j;

    for( j = 0 ; j < 3 ; j++ ) {
	
	for( i = 0 ; i < mesh->mesh.nPoints ; i++) {

	    fprintf(outFile,"%12.5e\n",(scalar)mesh->mesh.points[i][j]);    

	}

    }



    // Lattice elements
	
    if( mesh->lattice.model == D2Q9 ) {

	fprintf(outFile,"quad4\n");

	fprintf(outFile,"%10d\n", mesh->mesh.ncells);

	for( i = 0 ; i < mesh->mesh.ncells ; i++) {
	    
	    fprintf(outFile,"%10d ",mesh->mesh.vtkCells[i][0]+1);

	    fprintf(outFile,"%10d ",mesh->mesh.vtkCells[i][1]+1);

	    fprintf(outFile,"%10d ",mesh->mesh.vtkCells[i][3]+1);

	    fprintf(outFile,"%10d\n",mesh->mesh.vtkCells[i][2]+1);	    

	}

    }


    fclose(outFile);


}
