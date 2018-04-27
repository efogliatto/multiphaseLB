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

	    
	    if(  !lookUpScalarEntry("properties/macroProperties", "EOS/a_cs", 0, &info.eParam.csp.a)  )
		errorMsg("Unable to find constant a_cs");

	    
	    if(  !lookUpScalarEntry("properties/macroProperties", "EOS/b_cs", 0, &info.eParam.csp.b)  )
		errorMsg("Unable to find constant b_cs");	    

	}


	if( strcmp(eosType,"Peng-Robinson") == 0 ) {

	    info.etype = PengRob;

	    
	    if(  !lookUpScalarEntry("properties/macroProperties", "EOS/a_pr", 0, &info.eParam.prp.a)  )
		errorMsg("Unable to find constant a_pr");

	    
	    if(  !lookUpScalarEntry("properties/macroProperties", "EOS/b_pr", 0, &info.eParam.prp.b)  )
		errorMsg("Unable to find constant b_pr");


	    if(  !lookUpScalarEntry("properties/macroProperties", "EOS/w_pr", 0, &info.eParam.prp.omega)  )
		errorMsg("Unable to find constant w_pr");	    	    
	    
	}


	if( strcmp(eosType,"vanDerWaals") == 0 ) {

	    info.etype = VdW;

	    if(  !lookUpScalarEntry("properties/macroProperties", "EOS/a_vdw", 0, &info.eParam.vdwparam.a)  )
		errorMsg("Unable to find constant a_vdw");
	       
		
	    if(  !lookUpScalarEntry("properties/macroProperties", "EOS/b_vdw", 0, &info.eParam.vdwparam.b)  )
		errorMsg("Unable to find constant b_vdw");

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
