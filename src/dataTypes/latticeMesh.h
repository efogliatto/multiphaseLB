#ifndef LATTICEMESH_H
#define LATTICEMESH_H

/* #include <timeInfo.h> */
/* #include <latticeInfo.h> */
/* #include <vtkInfo.h> */
/* #include <bdInfo.h> */
/* #include <EOSInfo.h> */

#include <basicMesh.h>
#include <mpiInfo.h>

struct latticeMesh {


    // Mesh information
    struct basicMesh mesh;

    // Parallel structure
    struct mpiInfo parallel;

    

    /* // Time information */
    /* struct timeInfo time; */

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
