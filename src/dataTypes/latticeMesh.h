#ifndef LATTICEMESH_H
#define LATTICEMESH_H


/* #include <latticeInfo.h> */
/* #include <vtkInfo.h> */
/* #include <bdInfo.h> */
/* #include <EOSInfo.h> */

#include <basicMesh.h>
#include <mpiInfo.h>
#include <timeInfo.h>

struct latticeMesh {

    // Time information
    struct timeInfo time;


    // Mesh information
    struct basicMesh mesh;

    // Parallel structure
    struct mpiInfo parallel;

    


    /* // DdQq information */
    /* struct latticeInfo lattice; */

    /* // Parallel structure */
    /* struct mpiInfo parallel; */

    /* // Neighbour indexing */
    /* int** nb; */

    /* // VTK properties */
    /* struct vtkInfo vtk; */

    /* // Boundary elements */
    /* struct bdInfo bdElements; */

    /* // EOS information */
    /* struct EOSInfo EOS; */
};



#endif // LATTICEMESH_H
