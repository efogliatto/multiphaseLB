#ifndef LATTICEMESH_H
#define LATTICEMESH_H


/* #include <latticeInfo.h> */
/* #include <vtkInfo.h> */
/* #include <bdInfo.h> */
/* #include <EOSInfo.h> */

#include <basicMesh.h>
#include <mpiInfo.h>
#include <timeInfo.h>
#include <latticeInfo.h>
#include <EOSInfo.h>

struct latticeMesh {


    
    // Time information
    
    struct timeInfo time;


    
    // Mesh information
    
    struct basicMesh mesh;


    
    // Parallel structure
    
    struct mpiInfo parallel;


    
    // DdQq model information

    struct latticeInfo lattice;
    


    // EOS information

    struct EOSInfo EOS;
    
};



#endif // LATTICEMESH_H
