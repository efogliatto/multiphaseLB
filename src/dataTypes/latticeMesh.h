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

/**
 * @file latticeMesh.h
 * @author Ezequiel O. Fogliatto
 * @date 15 Dic 2017
 * @brief Full mesh information
 */

/**
 * @brief Full mesh information
 *
 * Full mesh information
 */

typedef struct {


    /** Time information */
    struct timeInfo time;          

    /** Mesh information */
    basicMesh mesh;         

    /** Parallel structure */
    struct mpiInfo parallel;       

    /** DdQq model information */
    latticeInfo lattice;    

    /** EOS information */
    struct EOSInfo EOS;            
    
} latticeMesh;



#endif // LATTICEMESH_H
