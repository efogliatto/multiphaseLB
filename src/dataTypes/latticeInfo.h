#ifndef LATTICEINFO_H
#define LATTICEINFO_H

// Basically, DdQq model info

/**
 * @file latticeInfo.h
 * @author Ezequiel O. Fogliatto
 * @date 15 Dic 2017
 * @brief Lattice model parameters
 */

/**
 * @brief Lattice model parameters
 *
 * Lattice model parameters
 */

struct latticeInfo {

    double cs2;    /**< Sound speed */

    int d;    /**< Dimension */

    int Q;    /**< Number of discrete velocities */

    int** vel;    /**< DdQq model velocities */

    int* reverse;    /**< DdQq model reverse indices */
    
    double* omega;    /**< DdQq model weights */

    double* weights;    /**< Interaction force weights */

    double** M;    /**< MRT transformation matrix */

    double** invM;    /**< MRT inverse of transformation matrix */
    
};

#endif // LATTICEINFO_H
