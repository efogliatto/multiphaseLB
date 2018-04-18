#ifndef BASICMESH_H
#define BASICMESH_H

/**
 * @file basicMesh.h
 * @author Ezequiel O. Fogliatto
 * @date 15 Dic 2017
 * @brief Mesh information
 */



/**
 * @brief Boundary information
 *
 * Information about boundary elements
 */

typedef struct {
    
    unsigned int nbd;         /**< Number of boundary types */
    
    unsigned int* nbdelem;    /**< Total number of elements per boundary type */
    
    char bdNames[100][100];   /**< Boundary names (max 100 boundaries) */
    
    unsigned int** bdPoints;  /**< Elements in boundary */

} basicBoundary;



/**
 * @brief Basic lattice information
 *
 * Lattice information
 */

typedef struct {

    
    unsigned int nPoints;   /**< Total number of points per patch */
    
    int** points;   /**< Points coordinates array */
    

    
    unsigned int Q;   /**< Total number of neighbours */
    
    char lbm[100];   /**< LB lattice model (DdQq type) */
    
    int** nb;   /**< Neighbour indices array */


    
    basicBoundary bd;   /**< Boundary information */

    
    unsigned int ncells;   /**< Number of VTK cells per patch */
    
    unsigned int cellType;   /**< VTK cell type */
    
    int** vtkCells;   /**< VTK cell indices array */

} basicMesh;





#endif // BASICMESH_H
