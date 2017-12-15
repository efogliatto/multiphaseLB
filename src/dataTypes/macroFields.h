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

    double* rho; /**< Macroscopic density field */

    double* p;  /**< Macroscopic pressure field */

    double** U;  /**< Macroscopic velocity field */

    double* T;  /**< Macroscopic temperature field */

    double** Fi; /**< Macroscopic interaction force field */

    double* phiDivU; /**< Macroscopic compression work field */
    
    /* // Constants */

    /* // Specific heat */
    /* double Cv; */
    
};

#endif // MACROFIELDS_H
