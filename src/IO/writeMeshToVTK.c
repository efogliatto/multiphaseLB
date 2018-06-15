#include <latticeMesh.h>
#include <vtkInfo.h>
#include <stdio.h>
#include <stdlib.h>

void writeMeshToVTK( latticeMesh* mesh, vtkInfo* vtk ) {

    
    FILE *outFile;

    char fileName[100];

    int status;

    // Create folder
    sprintf(fileName, "mkdir -p processor%d/%d", mesh->parallel.pid, mesh->time.current);
    status = system(fileName);

    if(status){}


    // Open file
    sprintf(fileName, "processor%d/%d/fields.vtu", mesh->parallel.pid, mesh->time.current);

    outFile = fopen(fileName, "w");



    // Print header
    fprintf(outFile, "<?xml version=\"1.0\"?>\n");
    fprintf(outFile, "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\" compressor=\"vtkZLibDataCompressor\">\n");
    fprintf(outFile, "  <UnstructuredGrid>\n");
    fprintf(outFile, "    <Piece NumberOfPoints=\"%d\" NumberOfCells=\"%d\">\n", mesh->mesh.nPoints, mesh->mesh.ncells);
    fprintf(outFile, "      <Points>\n");
    fprintf(outFile, "        <DataArray type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">\n");

    
    // Write points
    uint i;
    for( i = 0 ; i < mesh->mesh.nPoints ; i++ ) {
    	fprintf(outFile, "          %.1f %.1f %.1f\n", (float)mesh->mesh.points[i][0], (float)mesh->mesh.points[i][1], (float)mesh->mesh.points[i][2]);
    }
    

    fprintf(outFile, "        </DataArray>\n");
    fprintf(outFile, "      </Points>\n");
    fprintf(outFile, "      <Cells>\n");
    fprintf(outFile, "        <DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">\n");

    // Write cells
    uint j;
    
    for( i = 0 ; i < mesh->mesh.ncells ; i++ ) {

	fprintf(outFile, "          ");

	for( j = 0 ; j < mesh->mesh.cellType ; j++ ) {

	    fprintf(outFile, "%d ", mesh->mesh.vtkCells[i][j]);
    	}
	
    	fprintf(outFile, "\n");
	
    }


    

    fprintf(outFile, "        </DataArray>\n");

    fprintf(outFile, "        <DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">\n");


    // Write offsets
    uint acum = 0;
    for( i = 0 ; i < mesh->mesh.ncells ; i++ ) {
    	acum += mesh->mesh.cellType;
    	fprintf(outFile, "          %d\n", acum);
    }


    fprintf(outFile, "        </DataArray>\n");
    fprintf(outFile, "        <DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">\n");


    // Write cell type
    for( i = 0 ; i < mesh->mesh.ncells ; i++ ) {
    	fprintf(outFile, "          8\n");
    }


    fprintf(outFile, "        </DataArray>\n");
    fprintf(outFile, "      </Cells>\n");

    // Write field names
    fprintf(outFile, "      <PointData Scalars=\"");
    for( i = 0 ; i < vtk->nscalar ; i++ ) {
	if(i == (vtk->nscalar - 1)) {
	    fprintf(outFile, "%s", vtk->scalarFields[i]);
	}
	else {	    
	    fprintf(outFile, "%s ", vtk->scalarFields[i]);
	}
    }

    fprintf(outFile, "\" Vectors=\"");
    for( i = 0 ; i < vtk->nvector ; i++ ) {
    	fprintf(outFile, "%s ", vtk->vectorFields[i]);
    }
    for( i = 0 ; i < vtk->npdf ; i++ ) {
	if(i == (vtk->npdf - 1)) {
	    fprintf(outFile, "%s", vtk->pdfFields[i]);
	}
	else {
	    fprintf(outFile, "%s ", vtk->pdfFields[i]);
	}
    }

    
    fprintf(outFile, "\">\n");
    
    fclose(outFile);





    // Write in time folder
    if( mesh->parallel.pid == 0 ) {

	// Create folder
	sprintf(fileName, "mkdir -p %d", mesh->time.current);
	status = system(fileName);


	// Open file
	sprintf(fileName, "%d/fields.pvtu", mesh->time.current);
	outFile = fopen(fileName, "w");


	// Write header
	fprintf(outFile, "<?xml version=\"1.0\"?>\n");
	fprintf(outFile, "<VTKFile type=\"PUnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">\n");
	fprintf(outFile, "  <PUnstructuredGrid GhostLevel=\"0\">\n");


	// Write fields info
	fprintf(outFile, "    <PPointData Scalars=\"");
	for( i = 0 ; i < vtk->nscalar ; i++ ) {
	    if(i == (vtk->nscalar - 1)) {
		fprintf(outFile, "%s", vtk->scalarFields[i]);
	    }
	    else {	    
		fprintf(outFile, "%s ", vtk->scalarFields[i]);
	    }
	}

	fprintf(outFile, "\" Vectors=\"");
	for( i = 0 ; i < vtk->nvector ; i++ ) {
	    fprintf(outFile, "%s ", vtk->vectorFields[i]);
	}
	for( i = 0 ; i < vtk->npdf ; i++ ) {
	    if(i == (vtk->npdf - 1)) {
		fprintf(outFile, "%s", vtk->pdfFields[i]);
	    }
	    else {
		fprintf(outFile, "%s ", vtk->pdfFields[i]);
	    }
	}

	fprintf(outFile, "\">\n");

	

	// Write scalar fields info
	for (i = 0 ; i < vtk->nscalar ; i++) {
	    fprintf(outFile, "      <PDataArray type=\"Float32\" Name=\"%s\"/>\n", vtk->scalarFields[i]);
	}

	// Write vector fields info
	for (i = 0 ; i < vtk->nvector ; i++) {
	    fprintf(outFile, "      <PDataArray type=\"Float32\" Name=\"%s\" NumberOfComponents=\"3\"/>\n", vtk->vectorFields[i]);
	}

	// Write pdf fields info
	for (i = 0 ; i < vtk->npdf ; i++) {
	    fprintf(outFile, "      <PDataArray type=\"Float32\" Name=\"%s\" NumberOfComponents=\"%d\"/>\n", vtk->pdfFields[i], mesh->mesh.Q);
	}		



	fprintf(outFile, "    </PPointData>\n");
	fprintf(outFile, "    <PPoints>\n");
	fprintf(outFile, "      <PDataArray type=\"Float32\" NumberOfComponents=\"3\"/>\n");
	fprintf(outFile, "    </PPoints>\n");
	for (i = 0 ; i < mesh->parallel.worldSize ; i++) {
	    fprintf(outFile, "    <Piece Source=\"../processor%d/%d/fields.vtu\"/>\n", i, mesh->time.current);
	}
	fprintf(outFile, "  </PUnstructuredGrid>\n");
	fprintf(outFile, "</VTKFile>\n");


	
	fclose(outFile);

    }


}
