#ifndef WRITEMESHTOVTK_H
#define WRITEMESHTOVTK_H

#include <latticeMesh.h>
#include <vtkInfo.h>

void writeMeshToVTK( struct latticeMesh* mesh, struct vtkInfo* vtk );

#endif // WRITEMESHTOVTK_H
