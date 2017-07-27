#ifndef MACROFIELDS_H
#define MACROFIELDS_H

struct macroFields {

    // Density
    double* rho;

    // Pressure
    double* p;

    // Velocity
    double** U;

    // Temperature
    double* T;



    // Interaction force
    double** Fi;

    // Compresion work
    double* phiDivU;
    
    /* // Constants */

    /* // Specific heat */
    /* double Cv; */
    
};

#endif // MACROFIELDS_H
