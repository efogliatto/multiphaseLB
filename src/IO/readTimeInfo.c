#include <readTimeInfo.h>
#include <dictIO.h>
#include <basic.h>

void readTimeInfo( latticeMesh* mesh ) {

    
    scalar aux;

    uint status;

    
    // Start time

    status = lookUpScalarEntry("properties/simulation","startTime",0, &aux);

    if(status) {}
    
    mesh->time.start = (uint)aux;

    mesh->time.current = mesh->time.start;

    mesh->time.stp = 0;
    


    // End time

    status = lookUpScalarEntry("properties/simulation", "endTime", 0, &aux);

    if(status) {}
    
    mesh->time.end = (uint)aux;


    
    // Write interval

    status = lookUpScalarEntry("properties/simulation","writeInterval", 1, &aux);

    if(status) {}
    
    mesh->time.writeInterval = (uint)aux;



    // Measure time

    mesh->time.st = time( NULL );

    gettimeofday( &mesh->time.stt, NULL );



    /* // Debug flag */

    /* char* debug; */

    /* mesh->time.debug = 0; */
    
    /* status = lookUpStringEntry("properties/simulation","writeDebug", &debug, "no"); */

    /* if(status) {} */

    /* if( strcmp(debug,"yes") == 0 ) { */
    
    /* 	mesh->time.debug = 1; */

    /* } */

    /* free(debug); */





    // Data Format
    
    char* fmt;
    
    status = lookUpStringEntry("properties/simulation","dataFormat", &fmt, "asciiRaw");

    if(status) {}

    if( strcmp(fmt,"asciiRaw") == 0 ) {
    
    	mesh->time.data = asciiRaw;

    }

    else {

	if( strcmp(fmt,"pvtu") == 0 ) {
    
	    mesh->time.data = pvtu;

	}

	else {

	    errorMsg("Data format not recognized");

	}

    }

    free(fmt);

    
}
