#ifndef BASICMESH_H
#define BASICMESH_H

/**
 * @file basicMesh.h
 * @author Ezequiel O. Fogliatto
 * @date 15 Dic 2017
 * @brief Mesh information
 */

#include <dataTypes.h>

/**
 * @brief Boundary information
 *
 * Information about boundary elements
 */

typedef struct {
    
    uint nbd;         /**< Number of boundary types */
    
    uint* nbdelem;    /**< Total number of elements per boundary type */
    
    char bdNames[100][100];   /**< Boundary names (max 100 boundaries) */
    
    uint** bdPoints;  /**< Elements in boundary */

} basicBoundary;



/**
 * @brief Basic lattice information
 *
 * Lattice information
 */

typedef struct {

    
    uint nPoints;   /**< Total number of points per patch */
    
    int** points;   /**< Points coordinates array */
    

    
    uint Q;   /**< Total number of neighbours */
    
    char lbm[100];   /**< LB lattice model (DdQq type) */
    
    int** nb;   /**< Neighbour indices array */


    
    basicBoundary bd;   /**< Boundary information */

    
    uint ncells;   /**< Number of VTK cells per patch */
    
    uint cellType;   /**< VTK cell type */
    
    int** vtkCells;   /**< VTK cell indices array */


  /** Flag to check if node is on boundary */
  
    uint* isOnBnd;

} basicMesh;





#endif // BASICMESH_H
