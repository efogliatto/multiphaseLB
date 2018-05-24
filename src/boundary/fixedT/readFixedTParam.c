#include <readFixedTParam.h>
#include <basic.h>
#include <dictIO.h>

fixedTParam readFixedTParam( char* fname, char* bdname ) {

    char* entry;

    unsigned int status = 0;

    fixedTParam param;



    /* Read boundary value */

    status = vstring(&entry, "%s/%s/value", fname, bdname);

    status = lookUpScalarEntry("start/boundaries", entry, 0, &param.T);

    if(!status) {

	char* msg;

	status = vstring(&msg, "Unable to find %s", entry);
	
	errorMsg(msg);

    }



    /* /\* Read boundary perturbation *\/ */

    /* status = vstring(&entry, "%s/%s/pert", fname, bdname); */

    /* status = lookUpScalarEntry("start/boundaries", entry, 0, &param.p); */

    /* if(!status) { */

    /* 	param.p = 0; */

    /* 	param.psteps = 0; */

    /* 	param.localTStep = 1; */

    /* } */

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
