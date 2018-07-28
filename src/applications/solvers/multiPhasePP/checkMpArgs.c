#include <checkMpArgs.h>
#include <string.h>

mpOptions checkMpArgs( int argc, char **argv ) {

    mpOptions mp;

    
    // Check for arguments
    
    mp.ht = 1, mp.frozen = 1, mp.mthread = 0;
    
    {
	uint arg;
	
	for( arg = 0 ; arg < argc ; arg++) {

	    if ( strcmp("--nht", argv[arg]) == 0 ) {
		
		mp.ht = 0;
		
	    }

	    else {

		if ( strcmp("--frozen", argv[arg]) == 0 ) {
		    
		    mp.frozen = 0;
		    
		}


		else {

		    if ( strcmp("--mt", argv[arg]) == 0 ) {
		    
			mp.mthread = 1;
		    
		    }
		
		}		
		
	    }
	    
	}
    }



    return mp;

}
