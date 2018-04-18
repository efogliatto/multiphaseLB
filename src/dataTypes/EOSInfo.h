#ifndef EOSINFO_H
#define EOSINFO_H

/**
 * @file EOSInfo.h
 * @author Ezequiel O. Fogliatto
 * @date 15 Dic 2017
 * @brief Equation Of State parameters
 */

/**
 * @brief Equation Of State parameters
 *
 * Constants used in the selecter EOS
 */

typedef struct {

    /** EOS identifier
     *- 0 : ideal gas
     *- 1 : Carnahan-Starling
     *- 2 : Peng-Robinson
     *- 3 : van der Waals 
     */
    unsigned int _eosIdx;



    double _a;    /**< EOS constant */


    double _b;    /**< EOS constant */


    double _R;    /**< Gas constant */


    double _G;    /**< Interaction strength */


    double _M;    /**< Molar mass */


    double _omega;    /**< EOS constant */


    double _Cv;    /**< Constant specific heat */

    
    double _g[3];   /**< Gravity vector */

    
    double rho_0;  /**< Reference density (buoyant force) */
    
} EOSInfo;

#endif // EOSINFO_H
