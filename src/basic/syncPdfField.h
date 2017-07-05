#ifndef SYNCPDFFIELD_H
#define SYNCPDFFIELD_H

#include <latticeMesh.h>
#include <mpi.h>

void syncPdfField( struct latticeMesh* mesh, double** fld );

#endif // SYNCPDFFIELD_H
