#include <readFixedGradTParam.h>
#include <basic.h>
#include <dictIO.h>

fixedGradTParam readFixedGradTParam( char* fname, char* bdname ) {

    char* entry;

    uint status = 0;

    fixedGradTParam param;



    /* Read boundary value */

    status = vstring(&entry, "%s/%s/value", fname, bdname);

    status = lookUpScalarEntry("start/boundaries", entry, 0, &param.gradT);


    /** Read normal direction */

    status = vstring(&entry, "%s/%s/normal", fname, bdname);

    scalar nv;

    status = lookUpScalarEntry("start/boundaries", entry, 0, &nv);

    param.nv = (uint)nv;
    
    
    

    if(!status) {

	char* msg;

	status = vstring(&msg, "Unable to find %s", entry);
	
	errorMsg(msg);

    }



    /* Read boundary perturbation */

    status = vstring(&entry, "%s/%s/pert", fname, bdname);

    status = lookUpScalarEntry("start/boundaries", entry, 0, &param.pert);

    if(!status) {

    	param.pert = 0;

    	/* param.psteps = 0; */

    	/* param.localTStep = 1; */

    }

    /* else { */

    /* 	double steps = 0; */
	
    /* 	status = vstring(&entry, "%s/%s/duration", fname, bdname); */

    /* 	status = lookUpScalarEntry("start/boundaries", entry, 0, &steps); */

    /* 	if(!status) { */

    /* 	    char* msg; */

    /* 	    status = vstring(&msg, "Unable to find %s", entry); */
	
    /* 	    errorMsg(msg); */

    /* 	} */

    /* 	else { */

    /* 	    param.psteps = (int)steps; */

    /* 	    param.localTStep = 0; */

    /* 	} */
	
    /* } */


    
    return param;

}
