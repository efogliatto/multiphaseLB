#include <readDataFormat.h>
#include <dictIO.h>
#include <basic.h>

dataFormat readDataFormat() {


    // Data Format
    
    char* fmt;
    
    uint status = lookUpStringEntry("properties/simulation","dataFormat", &fmt, "asciiRaw");

    dataFormat data = asciiRaw;

    if(status) {}

    if( strcmp(fmt,"asciiRaw") == 0 ) {
    
    	data = asciiRaw;

    }

    else {

	if( strcmp(fmt,"pvtu") == 0 ) {
    
	    data = pvtu;

	}

	else {

	    if( strcmp(fmt,"binaryRaw") == 0 ) {
    
		data = binaryRaw;

	    }

	    else {
	    
		if( strcmp(fmt,"ensight") == 0 ) {
    
		    data = ensight;

		}

		else {
	    
		    errorMsg("Data format not recognized");

		}	       

	    }

	}

    }

    free(fmt);



    return data;

    
}
