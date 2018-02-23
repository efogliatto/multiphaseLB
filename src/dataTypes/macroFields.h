#ifndef MACROFIELDS_H
#define MACROFIELDS_H

/**
 * @file macroFields.h
 * @author Ezequiel O. Fogliatto
 * @date 15 Dic 2017
 * @brief Struct containing arrays for macroscopic fields
 */

/**
 * @brief Struct containing arrays for macroscopic fields
 *
 * This struct contains arrays for all macroscopic fields, wether they are used or not.
 */

struct macroFields {

    
    /** Macroscopic density field */
    
    double* rho; 

    
    /** Macroscopic pressure field */
    
    double* p;  


    /** Macroscopic velocity field */
    
    double** U;  

    
    /** Macroscopic temperature field */
    
    double* T;  


    /** Macroscopic interaction force field */
    
    double** Fi; 

    
    /** Macroscopic scalar source term */
    
    double* scalarSource; 
    
    
};

#endif // MACROFIELDS_H
