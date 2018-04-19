#include <readLiMRTConstants.h>
#include <dictIO.h>
#include <basic.h>


liMRTConstants readLiMRTConstants( char* fname ) {

    
    liMRTConstants param;

    char* msg;

    unsigned int status;

    

    // Relaxation times

    unsigned int n;

    status = vstring(&msg, "%s/Lambda", fname);
	
    if( !lookUpVectorEntry("properties/macroProperties", msg, &param.Lambda, &n) ) {

	status = vstring(&msg, "Ill defined entry %s/Lambda", fname);

	if(status)	
	    errorMsg( msg );

    }



    // Sigma

    status = vstring(&msg, "%s/sigma", fname);
	
    if( !lookUpScalarEntry("properties/macroProperties", msg, 0, &param.sigma) ) {

	status = vstring(&msg, "Ill defined entry %s/sigma", fname);

	if(status)
	    errorMsg( msg );

    }    
    
	
    

    return param;

}
