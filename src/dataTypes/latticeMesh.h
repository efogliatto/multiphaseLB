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

struct latticeMesh {

    
    struct timeInfo time;          /**< Time information */
    
    struct basicMesh mesh;         /**< Mesh information */
    
    struct mpiInfo parallel;       /**< Parallel structure */

    struct latticeInfo lattice;    /**< DdQq model information */

    struct EOSInfo EOS;            /**< EOS information */
    
};



#endif // LATTICEMESH_H
