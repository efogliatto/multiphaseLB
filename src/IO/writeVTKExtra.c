#include <latticeMesh.h>
#include <vtkInfo.h>
#include <stdio.h>
#include <stdlib.h>

void writeVTKExtra( latticeMesh* mesh, struct vtkInfo* vtk ) {

    int status;
    
    FILE *outFile;

    char fileName[100];


    // Open file
    sprintf(fileName, "processor%d/%d/fields.vtu", mesh->parallel.pid, mesh->time.current);

    outFile = fopen(fileName, "a");

    fprintf(outFile, "      </PointData>\n");
    fprintf(outFile, "    </Piece>\n");
    fprintf(outFile, "  </UnstructuredGrid>\n");
    fprintf(outFile, "</VTKFile>\n");

    fclose(outFile);



    /* // Write case.pvd  */

    /* if(   ( mesh->parallel.pid == 0 )   &&  ( mesh->time.start != 0 )   ){ */
    
    /* 	// Remove last two lines */
    /* 	char cmd[100]; */
    /* 	sprintf(cmd, "head -n -2 < case.pvd > case2.pvd"); */
    /* 	status = system(cmd); */

    /* 	sprintf(cmd, "mv case2.pvd case.pvd"); */
    /* 	status = system(cmd); */


    /* 	// Open file */
    /* 	sprintf(fileName, "case.pvd"); */
    /* 	outFile = fopen(fileName, "a"); */
	
    /* 	// Add line */
    /* 	fprintf(outFile, "    <DataSet part=\"0\"  timestep=\"%d\" file=\"%d/fields.pvtu\" />\n", mesh->time.current, mesh->time.current ); */
    /* 	fprintf(outFile, "  </Collection>\n"); */
    /* 	fprintf(outFile, "</VTKFile>\n"); */


    /* 	fclose(outFile); */
	
    /* } */


    if (status) {}

}
