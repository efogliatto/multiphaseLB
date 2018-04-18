#include <stdio.h>
#include <EOSInfo.h>
#include <lookUpDouble.h>
#include <lookUpVector.h>
#include <lookUpString.h>
#include <string.h>
#include <stdlib.h>

EOSInfo readEOSInfo() {


    EOSInfo info;

    unsigned int status = 0;
    


    // EOS Type
    
    char eosType[100];

    status += lookUpString("properties/macroProperties", "EOS/model", eosType);

    if( strcmp(eosType,"idealGas") == 0 ) {

	info._eosIdx = 0;

    }

    else {

	if( strcmp(eosType,"Carnahan-Starling") == 0 ) {

	    info._eosIdx = 1;

	}


	else {

	    if( strcmp(eosType,"Peng-Robinson") == 0 ) {

		info._eosIdx = 2;

	    }


	    else {

		if( strcmp(eosType,"vanDerWaals") == 0 ) {

		    info._eosIdx = 3;

		}

		else {

		    printf("\n   [ERROR]  Unrecognized EOS %s\n\n", eosType);

		    exit(1);

		}

	    }		    

	}

	

    }
    



    // Model constants
    
    status = lookUpDouble( "properties/macroProperties", "EOS/a", &info._a, 0 );

    status = lookUpDouble( "properties/macroProperties", "EOS/b", &info._b, 0 );

    status = lookUpDouble( "properties/macroProperties", "EOS/R", &info._R, 1 );

    status = lookUpDouble( "properties/macroProperties", "EOS/G", &info._G, -1 );

    status = lookUpDouble( "properties/macroProperties", "EOS/M", &info._M, 1 );

    status = lookUpDouble( "properties/macroProperties", "EOS/omega", &info._omega, 0 );

    status = lookUpDouble( "properties/macroProperties", "EOS/Cv", &info._Cv, 1 );

    status = lookUpDouble( "properties/macroProperties", "EOS/rho_0", &info.rho_0, 0 );

    status = lookUpVector( "properties/macroProperties", "EOS/g", info._g, 3 );


    
    
    return info;

}
