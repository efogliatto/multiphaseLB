#include <readLiMRTConstants.h>
#include <dictIO.h>
#include <basic.h>


liMRTConstants readLiMRTConstants( char* fname ) {

    liMRTConstants param;

    char* msg;

    size_t strl;
    

    // Relaxation times

    unsigned int n;

    strl = snprintf(NULL, 0, "%s/Lambda", fname);

    

    /* msg = asprintf("%s/Lambda", fname); */

    /* if( !lookUpVectorEntry("properties/macroProperties", asprintf("%s/Lambda",fname), &param.Lambda, &n) ) */
    /* 	errorMsg( asprintf("Ill defined entry %s/Lambda",fname) ); */
	
    

    return param;

}
