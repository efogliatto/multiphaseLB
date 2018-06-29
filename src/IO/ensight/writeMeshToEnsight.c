#include <latticeMesh.h>
#include <stdio.h>
#include <stdlib.h>
#include <writeMeshToEnsight.h>
#include <basic.h>
#include <vtkInfo.h>
#include <readVTKInfo.h>

void writeMeshToEnsight( latticeMesh* mesh ) {

    FILE *outFile;

    char fileName[100];


   
    // Write Mesh
    
    sprintf(fileName, "lattice.geo");


    // Headers first

    if( mesh->parallel.pid == 0 ) {

	    
	// Open File
	    
	outFile = fopen(fileName, "w");
    
	
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




	// .case file

	vtkInfo vtk = readVTKInfo();

	

	// Open File
	    
	outFile = fopen("lbm.case", "w");


	fprintf(outFile,"#\n");
	fprintf(outFile,"# EnSight 7.4.1 ((n))\n");
	fprintf(outFile,"# Case File: lattice.case\n");
	fprintf(outFile,"\n");
	fprintf(outFile,"FORMAT\n");
	fprintf(outFile,"\n");
	fprintf(outFile,"type:  ensight gold\n");
	fprintf(outFile,"\n");
	fprintf(outFile,"GEOMETRY\n");
	fprintf(outFile,"\n");
	fprintf(outFile,"model:                     lattice.geo\n");
	fprintf(outFile,"\n");
	fprintf(outFile,"VARIABLE\n");
	fprintf(outFile,"\n");

	uint fid;
		
    	for( fid = 0 ; fid < vtk.nscalar ; fid++ ) {

	    fprintf(outFile,"scalar per node:           %s lattice.%s*\n",vtk.scalarFields[fid],vtk.scalarFields[fid]);
	    
	}

    	for( fid = 0 ; fid < vtk.npdf ; fid++ ) {

	    uint k;

	    for( k = 0 ; k < mesh->lattice.Q ; k++ ) {
	    
		fprintf(outFile,"scalar per node:           %s%d lattice.%s%d*\n",vtk.pdfFields[fid],k,vtk.pdfFields[fid],k);

	    }
	    
	}
	
    	for( fid = 0 ; fid < vtk.nvector ; fid++ ) {

	    fprintf(outFile,"vector per node:           %s lattice.%s*\n",vtk.vectorFields[fid],vtk.vectorFields[fid]);
	    
	}


	
	fprintf(outFile,"\n");	
	fprintf(outFile,"TIME\n");
	fprintf(outFile,"time set:                  1\n");
	fprintf(outFile,"number of steps:           1\n");
	fprintf(outFile,"filename start number:     0\n");
	fprintf(outFile,"filename increment:        1\n");
	fprintf(outFile,"time values:               0.0 ");

	fclose(outFile);
	

    }



    // Points coordinates

    outFile = fopen(fileName, "a");

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
