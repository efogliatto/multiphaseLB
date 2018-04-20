#ifndef EOSINFO_H
#define EOSINFO_H

/**
 * @file EOSInfo.h
 * @author Ezequiel O. Fogliatto
 * @date 20 Apr 2018
 * @brief Equation Of State parameters
 */


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

    double a;

    double b;
	    
} VdWp;


typedef struct {

    double a;

    double b;
	    
} CarStarp;


typedef struct {

    double a;

    double b;

    double omega;
	    
} PengRobp;



typedef union {

    VdWp vdwparam;

    CarStarp csp;

    PengRobp prp;
	

} eosParam;



typedef struct {


    eosType etype;

    eosParam eParam;

    double R;    /**< Gas constant */

    double G;    /**< Interaction strength */

    double M;    /**< Molar mass */

    double Cv;    /**< Constant specific heat */
    
    double* g;   /**< Gravity vector */
    
    double rho_0;  /**< Reference density (buoyant force) */
    
    
} EOSInfo;

#endif // EOSINFO_H
