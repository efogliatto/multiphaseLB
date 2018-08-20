#include <readLiTempMRTConstants.h>
#include <dictIO.h>
#include <basic.h>


liTempMRTConstants readLiTempMRTConstants( char* fname ) {

    
    liTempMRTConstants param;

    char* msg;

    uint status;

    

    // Relaxation times

    uint n;

    status = vstring(&msg, "%s/Lambda", fname);
	
    if( !lookUpVectorEntry("properties/macroProperties", msg, &param.Lambda, &n) ) {

	status = vstring(&msg, "Ill defined entry %s/Lambda", fname);

	if(status)	
	    errorMsg( msg );

    }

    
    

    return param;

}
