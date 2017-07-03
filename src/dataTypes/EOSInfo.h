#ifndef EOSINFO_H
#define EOSINFO_H

struct EOSInfo {

    // EOS index
    // 0 : ideal gas
    // 1 : Carnahan-Starling
    // 2 : Peng-Robinson
    // 3 : van der Waals
    unsigned int _eosIdx;


    // Coefficients
    double _a;
    double _b;
    double _R;
    double _G;
    double _M;
    double _omega;

    // Constant specific heat
    double _Cv;

    // Gravity vector
    double _g[3];

    // Reference density
    double rho_0;    
    
};

#endif // EOSINFO_H
