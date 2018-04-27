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




    // Surface tension

    status = vstring(&msg, "%s/SurfaceTension", fname);

    char* aux;

    if( lookUpStringEntry("properties/macroProperties", msg, &aux, "none") ) {

	if( strcmp(aux, "none") == 0 ) {

	    param.surfaceTension = no_st;

	}

	else {

	    if( strcmp(aux, "liSurfTen") == 0 ) {

		
		param.surfaceTension = liSurfTen;


		// Look up kappa

		status = vstring(&msg, "%s/kappa_st", fname);

		if( !lookUpScalarEntry("properties/macroProperties", msg, -1, &param.kappa_st) ) {

		    status = vstring(&msg, "Unable to find %s/kappa_st", fname);

		    errorMsg( msg );

		}
		
		
	    }

	}

    }

    else {

	param.surfaceTension = no_st;

    }
	

    return param;

}
