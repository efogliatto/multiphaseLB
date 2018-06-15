#include <readMyMRTConstants.h>
#include <dictIO.h>
#include <basic.h>


myMRTConstants readMyMRTConstants( char* fname ) {

    
    myMRTConstants param;

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



    // Alpha_1

    status = vstring(&msg, "%s/alpha_1", fname);
	
    if( !lookUpScalarEntry("properties/macroProperties", msg, 0, &param.alpha_1) ) {

	status = vstring(&msg, "Ill defined entry %s/alpha_1", fname);

	if(status)
	    errorMsg( msg );

    }    

    
    // Alpha_2

    status = vstring(&msg, "%s/alpha_2", fname);
	
    if( !lookUpScalarEntry("properties/macroProperties", msg, 0, &param.alpha_2) ) {

	status = vstring(&msg, "Ill defined entry %s/alpha_2", fname);

	if(status)
	    errorMsg( msg );

    }    
    
    

    return param;

}
