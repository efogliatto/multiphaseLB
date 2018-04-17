#ifndef LATTICEINFO_H
#define LATTICEINFO_H


/**
 * @file latticeInfo.h
 * @author Ezequiel O. Fogliatto
 * @date 15 Dic 2017
 * @brief Lattice model parameters
 */


/**
 * @brief Available lattice models
 *
 * Available lattice models. DdQq type.
 */

typedef enum {
    D2Q9,
    D3Q15
} DdQq;


/**
 * @brief Lattice model parameters
 *
 * Lattice model parameters. DdQq related constants (d, Q, weights, etc.).
 */

typedef struct {

    /** General lattice model */
    DdQq model;
    
    /** Sound speed */
    double cs2;    

    /** Dimension */
    int d;    

    /** Number of discrete velocities */
    int Q;    

    /** DdQq model velocities */
    int** vel;    

    /** DdQq model reverse indices */
    int* reverse;    

    /** DdQq model weights */
    double* omega;    

    /** Interaction force weights */
    double* weights;    

    /** MRT transformation matrix */
    double** M;    

    /** MRT inverse of transformation matrix */
    double** invM;    
    
}latticeInfo;

#endif // LATTICEINFO_H
