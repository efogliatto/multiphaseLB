#ifndef LBEFIELD_H
#define LBEFIELD_H

#include <stdio.h>

// Boundary information

struct bdField {

    // Boundary condition index
    // 0: periodic
    // 1: bounceBack
    // 2: fixedU
    // 3: fixedT
    unsigned int bdType;
    
    double scalarVal;

    double vectorVal[3];

};
    

    
struct lbeField {

    
    // Distribution functions
    double** value;

    // Swap value
    double** swap;
    
    /* // Field name */
    /* char* name; */
    
    // Collision model id
    // 0: Li MRT 
    // 1: Li SRT
    // 2: Li SRT for temperature
    unsigned int colId;
    
    // Single relaxation time
    double tau;

    // Multiple relaxation times
    double* Lambda;

    // Force coefficient
    double sigma;

    // Thermal conductivity
    double lambda;

    // Relaxation time model
    // 0: constant
    // 1: constantMu
    // 2: constantLambda
    // 3: rho-dependent nu
    // 4: rho-dependent lambda
    unsigned int tauModel;


    // Extra constants used for tau dependency
    double ra;
    double rb;
    double na;
    double nb;

    
    // Boundary info. Related to basicBoundary in basicMesh
    struct bdField* boundary;
    
    
};

#endif // LBEFIELD_H
