#include <p_eos.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double rhoFromEOS( struct EOSInfo* info, double rho, double T, double p ) {

    double r;

    switch( info->_eosIdx ) {
   

    // van der Waals
    case 3:

	r = info->_R * T / ( p + info->_a * rho * rho / (info->_M*info->_M) )  +  info->_b;

	r = info->_M / r;       

	break;


    default:

	printf("  [ERROR]  density from EOS %d not implemented\n", info->_eosIdx);

	exit(0);
		
    }    
    
    return r;
    
}
