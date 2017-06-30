#ifndef LATTICEINFO_H
#define LATTICEINFO_H

// Basically, DdQq model info

struct latticeInfo {

    // Sound speed
    double cs2;

    // Dimension
    int d;

    // Number of discrete velocities
    int Q;

    // DdQq model velocities
    int** vel;

    // DdQq model reverse indices
    int* reverse;
    
    // DdQq model weights
    double* omega;

    // Interaction force weights
    double* weights;

    // MRT matrices
    double** M;

    double** invM;
    
};

#endif // LATTICEINFO_H
