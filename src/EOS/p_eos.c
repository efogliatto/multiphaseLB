#include <p_eos.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <basic.h>

scalar p_eos( EOSInfo* info, scalar rho, scalar T ) {

    scalar p = 0, alpha, beta;

    switch( info->etype ) {
    
    // Ideal Gas
    case ideal:
	
	p = rho * info->R * T;
	
	break;
    

    // Carnahan - Starling
    case CarStar:
	
	alpha = info->eParam.csp.b * rho / 4.0;

	beta  = 1 - alpha;

	p = rho * info->R * T * ( (1 + alpha + alpha*alpha - alpha*alpha*alpha) / ( beta*beta*beta )  ) - info->eParam.csp.a * rho * rho;

	break;

    
    // Peng - Robinson
    case PengRob:
	
	alpha = 0.170151343 * info->eParam.prp.a / (info->eParam.prp.b * info->R); // Tc
	
	beta = (1 + (0.37464+1.5422*info->eParam.prp.omega-0.26992*info->eParam.prp.omega*info->eParam.prp.omega)*(1-sqrt(T/alpha))); // sqrt(phi)
	
	p = rho * info->R * T / ( 1 - info->eParam.prp.b * rho)    -   info->eParam.prp.a * beta * beta * rho * rho / (1 + 2 * info->eParam.prp.b * rho - info->eParam.prp.b * rho * info->eParam.prp.b * rho);
	
	break;


    // van der Waals
    case VdW:
	
	p = rho * info->R * T / (info->M - rho * info->eParam.vdwparam.b)  -  info->eParam.vdwparam.a * rho * rho / ( info->M * info->M );
	
	break;

	
    default:

	errorMsg("EOS not defined");

	break;
	
	
    }    
    
    return p;
    
}
