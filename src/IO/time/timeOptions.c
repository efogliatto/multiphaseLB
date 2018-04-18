#include <timeInfo.h>


// Elapsed time
double elapsed ( timeInfo* info ) {

    struct timeval _end;
    
    gettimeofday( &_end, NULL );
	
    return (((double)_end.tv_sec + (double)_end.tv_usec / 1000000)  - ((double)info->stt.tv_sec + (double)info->stt.tv_usec / 1000000));

}


    
// Flag to enable writing
unsigned int writeFlag( timeInfo* info ) {

    unsigned int wrt = 0;
	
    if ( info->stp == info->writeInterval ) {
	
	wrt = 1;
	
    }

    return wrt;
	
}


    
// Update time structure
unsigned int updateTime( timeInfo* info ) {

    unsigned int upd = 1;

    
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
