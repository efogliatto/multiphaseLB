#ifndef LBEFIELD_H
#define LBEFIELD_H

#include <stdio.h>
#include <lbeModel.h>
#include <lbParameters.h>
#include <boundary.h>

/**
 * @file lbeField.h
 * @author Ezequiel O. Fogliatto
 * @date 15 Dic 2017
 * @brief Population field information
 */


/**
 * @brief Boundary information
 *
 * Boundary information
 * @todo Documentar
 * @return Nothing
 */

typedef struct {

    /** Boundary condition */
    bdType type;

    /** Boundary constants */
    bdParam param;

} bdField;
    

/**
 * @brief Population field
 *
 * Population field
 */
    
typedef struct {

    
    /** Distribution functions */
    double** value;

    /** Swap value */
    double** swap;

    /** Scalar source term  */
    double* scalarSource;
    
    // Field name
    char* name;

    /** Lattice - Boltzmann collision model */
    lbeModel model;

    /** Model-specific constants */
    lbParameters lbparam;
    
    /** Update tag */
    unsigned int update;    
    
    /** Boundary info. Related to basicBoundary in basicMesh */
    bdField* boundary;

    
} lbeField;

#endif // LBEFIELD_H
