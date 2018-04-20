#include <stdio.h>
#include <EOSInfo.h>
#include <string.h>
#include <stdlib.h>
#include <dictIO.h>
#include <basic.h>

EOSInfo readEOSInfo() {


    EOSInfo info;

    unsigned int status = 0;

    char* eosType;
    


    // EOS Type

    status = lookUpStringEntry("properties/macroProperties", "EOS/model", &eosType, "");

    if(status) {

	if( strcmp(eosType,"idealGas") == 0 ) {

	    info.etype = ideal;

	}


	if( strcmp(eosType,"Carnahan-Starling") == 0 ) {

	    info.etype = CarStar;

	}


	if( strcmp(eosType,"Peng-Robinson") == 0 ) {

	    info.etype = PengRob;

	}


	if( strcmp(eosType,"vanDerWaals") == 0 ) {

	    info.etype = VdW;

	    status = lookUpScalarEntry("properties/macroProperties", "EOS/a", 0, &info.eParam.vdwparam.a);

	    status = lookUpScalarEntry("properties/macroProperties", "EOS/b", 0, &info.eParam.vdwparam.b);

	}	
	
	

    }
    


    
    status = lookUpScalarEntry("properties/macroProperties", "EOS/R", 0, &info.R);

    status = lookUpScalarEntry("properties/macroProperties", "EOS/G", 0, &info.G);

    status = lookUpScalarEntry("properties/macroProperties", "EOS/M", 0, &info.M);

    status = lookUpScalarEntry("properties/macroProperties", "EOS/Cv", 0, &info.Cv);

    status = lookUpScalarEntry("properties/macroProperties", "EOS/rho_0", 0, &info.rho_0);


    unsigned int n;
    
    status = lookUpVectorEntry("properties/macroProperties", "EOS/g", &info.g, &n);



    
    
    return info;

}
