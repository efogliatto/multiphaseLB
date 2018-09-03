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

#include <dataTypes.h>

typedef struct {

    /** Macroscopic density field */
    
    scalar* rho; 

    
    /** Macroscopic pressure field */
    
    scalar* p;  


    /** Macroscopic velocity field */
    
    scalar** U;  

    
    /** Macroscopic temperature field */
    
    scalar* T;  


    /** Macroscopic interaction force field */
    
    scalar** Fi;


    /** Macroscopic total force field */
    
    scalar** Ft; 

    
    /** Macroscopic scalar source term */
    
    /* scalar* scalarSource; */

    /* scalar* oldss; */
    
    /* // Constants */

    /* // Specific heat */
    /* scalar Cv; */
    
} macroFields;

#endif // MACROFIELDS_H
