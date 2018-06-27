#include <latticeMesh.h>
#include <vtkInfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <writePvtuExtra.h>

void writePvtuExtra( latticeMesh* mesh, vtkInfo* vtk ) {

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


    if (status) {}

}
