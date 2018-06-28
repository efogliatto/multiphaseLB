#include <readFixedUParam.h>
#include <basic.h>
#include <dictIO.h>

fixedUParam readFixedUParam( char* fname, char* bdname ) {

    
    char* entry;

    uint status = 0;

    fixedUParam param;

    param.U[0] = 0;

    param.U[1] = 0;

    param.U[2] = 0;

    scalar* u;

    unsigned int n;


    status = vstring(&entry, "%s/%s/value", fname, bdname);

    status = lookUpVectorEntry("start/boundaries", entry, &u, &n);

    if(!status) {

    	char* msg;

    	status = vstring(&msg, "Unable to find %s", entry);
	
    	errorMsg(msg);

    }

    else {

	if( n != 3 ) {

	    char* msg;

	    status = vstring(&msg, "Ill defined vector %s value", entry);
	
	    errorMsg(msg);

	}

	else {

	    param.U[0] = u[0];

	    param.U[1] = u[1];

	    param.U[2] = u[2];	    

	}
	
    }

    
    return param;

}
