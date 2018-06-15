#ifndef EOSINFO_H
#define EOSINFO_H

/**
 * @file EOSInfo.h
 * @author Ezequiel O. Fogliatto
 * @date 20 Apr 2018
 * @brief Equation Of State parameters
 */


#include <dataTypes.h>


/** EOS identifier */

typedef enum {

    /** Ideal gas */
    ideal,

    /** Carnahan - Starling */
    CarStar,

    /** Peng - Robinson */
    PengRob,

    /** Van der Waals */
    VdW

} eosType;



/** EOS Constants */

typedef struct {

    scalar a;

    scalar b;
	    
} VdWp;


typedef struct {

    scalar a;

    scalar b;
	    
} CarStarp;


typedef struct {

    scalar a;

    scalar b;

    scalar omega;
	    
} PengRobp;



typedef union {

    VdWp vdwparam;

    CarStarp csp;

    PengRobp prp;
	

} eosParam;



typedef struct {


    eosType etype;

    eosParam eParam;

    scalar R;    /**< Gas constant */

    scalar G;    /**< Interaction strength */

    scalar M;    /**< Molar mass */

    scalar Cv;    /**< Constant specific heat */
    
    scalar* g;   /**< Gravity vector */
    
    scalar rho_0;  /**< Reference density (buoyant force) */
    
    
} EOSInfo;

#endif // EOSINFO_H
