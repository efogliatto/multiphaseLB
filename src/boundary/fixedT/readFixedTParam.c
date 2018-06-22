#include <readFixedTParam.h>
#include <basic.h>
#include <dictIO.h>

fixedTParam readFixedTParam( char* fname, char* bdname ) {

    char* entry;

    uint status = 0;

    fixedTParam param;



    /* Read boundary value */

    status = vstring(&entry, "%s/%s/value", fname, bdname);

    status = lookUpScalarEntry("start/boundaries", entry, 0, &param.T);

    if(!status) {

	char* msg;

	status = vstring(&msg, "Unable to find %s", entry);
	
	errorMsg(msg);

    }


    
    return param;

}
