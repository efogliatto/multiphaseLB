#ifndef LBEFIELD_H
#define LBEFIELD_H

#include <stdio.h>


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

struct bdField {

    /** Boundary condition tag
     *- 0: periodic
     *- 1: bounceBack
     *- 2: fixedU
     *- 3: fixedT  */
    unsigned int bdType;

    /** Scalar type boundary value (may be auxiliar) */
    double scalarVal;

    /** Vector type boundary value (may be auxiliar) */
    double vectorVal[3];

};
    

/**
 * @brief Population field
 *
 * Population field
 */
    
struct lbeField {

    
    /** Distribution functions */
    double** value;

    /** Swap value */
    double** swap;

    /** Scalar source term  */
    double* scalarSource;
    
    /* // Field name */
    /* char* name; */
    
    /** Collision model tag
     *- 0: Li MRT 
     *- 1: Li SRT
     *- 2: Li SRT for temperature
     *- 3: new SRT for temperature
     *- 4: new MRT for temperature
    */
    unsigned int colId;
    
    /** Single relaxation time */
    double tau;

    /** Multiple relaxation times */
    double* Lambda;

    /** Force coefficient */
    double sigma;

    /** Thermal conductivity */
    double lambda;

    /** Relaxation time tag
     *- 0: constant
     *- 1: constantMu
     *- 2: constantLambda
     *- 3: rho-dependent nu
     *- 4: rho-dependent lambda
    */
    unsigned int tauModel;


    /** Extra constants used for tau dependency */
    double ra;

    /** Extra constants used for tau dependency */
    double rb;

    /** Extra constants used for tau dependency */
    double na;

    /** Extra constants used for tau dependency */
    double nb;

    
    /** Extra constants used for equilibrium distributions in moment space (myMRTModel) */

    double alpha_1;

    double alpha_2;


    /** Update tag */

    unsigned int update;
    

    
    /** Boundary info. Related to basicBoundary in basicMesh */
    struct bdField* boundary;
    
    
};

#endif // LBEFIELD_H
