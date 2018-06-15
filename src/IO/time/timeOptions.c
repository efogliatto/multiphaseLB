#include <timeInfo.h>


// Elapsed time
scalar elapsed ( timeInfo* info ) {

    struct timeval _end;
    
    gettimeofday( &_end, NULL );
	
    return (((scalar)_end.tv_sec + (scalar)_end.tv_usec / 1000000)  - ((scalar)info->stt.tv_sec + (scalar)info->stt.tv_usec / 1000000));

}


    
// Flag to enable writing
uint writeFlag( timeInfo* info ) {

    uint wrt = 0;
	
    if ( info->stp == info->writeInterval ) {
	
	wrt = 1;
	
    }

    return wrt;
	
}


    
// Update time structure
uint updateTime( timeInfo* info ) {

    uint upd = 1;

    
    // Update time
    
    ++info->current;
    
    ++info->stp;


    if ( info->current > info->end ) {
	
	upd = 0;
	
    }

    
    if( info->stp > info->writeInterval) {
	
	info->stp = 1;
	
    }

	

    return upd;

}
